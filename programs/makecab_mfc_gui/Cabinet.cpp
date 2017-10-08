// Cabinet.cpp: implementation of the CCabinet class.
//
//////////////////////////////////////////////////////////////////////

#include "Cabinet.h"

#pragma warning(disable: 4996)

//下面是压缩时用到的回调函数。
/*
 * 分配内存
 */
FNFCIALLOC(mem_alloc)
{
	return malloc(cb);
}


/*
 * 释放内存
 */
FNFCIFREE(mem_free)
{
	free(memory);
}

/*
 * 打开文件
 */
FNFCIOPEN(fci_open)
{
    return _open(pszFile, oflag, pmode);
}

/*
 * 读取文件
 */
FNFCIREAD(fci_read)
{
    return (unsigned int) _read(hf, memory, cb);
}

/*
 * 写文件
 */
FNFCIWRITE(fci_write)
{
    return (unsigned int) _write(hf, memory, cb);
}

/*
 * 关闭文件
 */
FNFCICLOSE(fci_close)
{
   return _close(hf);
}

FNFCISEEK(fci_seek)
{
    return _lseek(hf, dist, seektype);
}

FNFCIDELETE(fci_delete)
{
    return remove(pszFile);
}


FNFCIFILEPLACED(file_placed)
{
	return 0;
}


FNFCIGETTEMPFILE(get_temp_file)
{
    char    *psz;

    psz = _tempnam("","xx");            // Get a name
    if ((psz != NULL) && (strlen(psz) < (unsigned)cbTempName)) {
        strcpy(pszTempName,psz);        // Copy to caller's buffer
        free(psz);                      // Free temporary name buffer
        return TRUE;                    // Success
    }
    //** Failed
    if (psz) {
        free(psz);
    }

    return FALSE;
}


/*
 * 用于压缩过程中的提示信息显示，这里忽略。
 */
FNFCISTATUS(progress)
{
	return 0;
}

/*
 * 这里忽略。
 */
FNFCIGETNEXTCABINET(get_next_cabinet)
{
	return TRUE;
}


FNFCIGETOPENINFO(get_open_info)
{
	BY_HANDLE_FILE_INFORMATION	finfo;
	FILETIME					filetime;
	HANDLE						handle;
    DWORD                       attrs;
    int                         hf;

    /*
     * Need a Win32 type handle to get file date/time
     * using the Win32 APIs, even though the handle we
     * will be returning is of the type compatible with
     * _open
     */
	handle = CreateFile(
		pszName,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
		NULL
	);
   
	if (handle == INVALID_HANDLE_VALUE)
	{
		return -1;
	}

	if (GetFileInformationByHandle(handle, &finfo) == FALSE)
	{
		CloseHandle(handle);
		return -1;
	}
   
	FileTimeToLocalFileTime(
		&finfo.ftLastWriteTime, 
		&filetime
	);

	FileTimeToDosDateTime(
		&filetime,
		pdate,
		ptime
	);

    attrs = GetFileAttributes(pszName);

    if (attrs == 0xFFFFFFFF)
    {
        /* failure */
        *pattribs = 0;
    }
    else
    {
        /*
         * Mask out all other bits except these four, since other
         * bits are used by the cabinet format to indicate a
         * special meaning.
         */
        *pattribs = (int) (attrs & (_A_RDONLY | _A_SYSTEM | _A_HIDDEN | _A_ARCH));
    }

    CloseHandle(handle);


    /*
     * Return handle using _open
     */
	hf = _open( pszName, _O_RDONLY | _O_BINARY );

	if (hf == -1)
		return -1; // abort on error
   
	return hf;
}
//以上为压缩时需要的回调函数


//下面是解压缩时用到的回调函数。

FNALLOC(dmem_alloc)
{
	return malloc(cb);
}

FNFREE(dmem_free)
{
	free(pv);
}

FNOPEN(dfile_open)
{
	return _open(pszFile, oflag, pmode);
}

FNREAD(dfile_read)
{
	return _read(hf, pv, cb);
}

FNWRITE(dfile_write)
{
	return _write(hf, pv, cb);
}

FNCLOSE(dfile_close)
{
	return _close(hf);
}

FNSEEK(dfile_seek)
{
	return _lseek(hf, dist, seektype);
}

char	dest_dir[MAX_PATH];

FNFDINOTIFY(notification_function)
{
	switch (fdint)
	{
		case fdintCABINET_INFO: // general information about the cabinet
			return 0;

		case fdintPARTIAL_FILE: // first file in cabinet is continuation
			return 0;

		case fdintCOPY_FILE:	// file to be copied
		{
			int		handle;
			char	destination[256];

			sprintf(
					destination, 
					"%s%s",
					dest_dir,
					pfdin->psz1
				);

				handle = _open(
					destination,
					_O_BINARY | _O_CREAT | _O_WRONLY | _O_SEQUENTIAL,
					_S_IREAD | _S_IWRITE 
				);

				return handle;
		}

		case fdintCLOSE_FILE_INFO:	// close the file, set relevant info
        {
            HANDLE  handle;
            DWORD   attrs;
            char    destination[256];

            sprintf(
                destination, 
                "%s%s",
                dest_dir,
                pfdin->psz1
            );

			_close(pfdin->hf);


            /*
             * Set date/time
             *
             * Need Win32 type handle for to set date/time
             */
            handle = CreateFile(
                destination,
                GENERIC_READ | GENERIC_WRITE,
                FILE_SHARE_READ,
                NULL,
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL,
                NULL
            );

            if (handle != INVALID_HANDLE_VALUE)
            {
                FILETIME    datetime;

                if (TRUE == DosDateTimeToFileTime(
                    pfdin->date,
                    pfdin->time,
                    &datetime))
                {
                    FILETIME    local_filetime;

                    if (TRUE == LocalFileTimeToFileTime(
                        &datetime,
                        &local_filetime))
                    {
                        (void) SetFileTime(
                            handle,
                            &local_filetime,
                            NULL,
                            &local_filetime
                        );
                     }
                }

                CloseHandle(handle);
            }

            /*
             * Mask out attribute bits other than readonly,
             * hidden, system, and archive, since the other
             * attribute bits are reserved for use by
             * the cabinet format.
             */
            attrs = pfdin->attribs;

            attrs &= (_A_RDONLY | _A_HIDDEN | _A_SYSTEM | _A_ARCH);

            (void) SetFileAttributes(
                destination,
                attrs
            );

			return TRUE;
        }

		case fdintNEXT_CABINET:	// file continued to next cabinet
			return 0;
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCabinet::CCabinet()
{

}

CCabinet::~CCabinet()
{

}

BOOL CCabinet::CreateCabinet(char *CABName)
{
	ERF				erf;
	CCAB			cab_parameters;

	char			*p;
	char			cabPath[MAX_PATH];
	char			cabName[MAX_PATH];

	if(CABName == NULL)
		return FALSE;

	p = strrchr(CABName, '\\');
	if (p == NULL)
	{
		strcpy(cabName, CABName);
		strcpy(cabPath, "");
	}
	else
	{
		strcpy(cabName, p+1);
		strncpy(cabPath, CABName, (int) (p-CABName)+1);
		cabPath[p - CABName + 1] = '\0';
	}


	memset(&cab_parameters, 0, sizeof(CCAB));

	cab_parameters.cb = MEDIA_SIZE;
	cab_parameters.cbFolderThresh = FOLDER_THRESHOLD;

	/*Don't reserve space for any extensions*/
	cab_parameters.cbReserveCFHeader = 0;
	cab_parameters.cbReserveCFFolder = 0;
	cab_parameters.cbReserveCFData   = 0;

	cab_parameters.iCab = 1;

	cab_parameters.iDisk = 0;

	/*Choose your own number*/
	cab_parameters.setID = 12345;

	/* where to store the created CAB files */
	strcpy(cab_parameters.szCabPath, cabPath);

	/* store name of CAB file */
	strcpy(cab_parameters.szCab, cabName);

	m_hfci = FCICreate(
		&erf,
		file_placed,
		mem_alloc,
		mem_free,
        fci_open,
        fci_read,
        fci_write,
        fci_close,
        fci_seek,
        fci_delete,
		get_temp_file,
        &cab_parameters,
        NULL
	);

	if (m_hfci == NULL)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CCabinet::AddFile2Cab(char *fileName)
{
	char			*p;
	char			srcName[MAX_PATH];

	if(fileName == NULL)
		return FALSE;

	p = strrchr(fileName, '\\');
	if (p == NULL)
	{
		strcpy(srcName, fileName);
	}
	else
	{
		strcpy(srcName, p+1);
	}

	if (FALSE == FCIAddFile(
			m_hfci,
			fileName,  /* file to add */
			srcName, /* file name in cabinet file */
			FALSE, /* file is not executable */
			get_next_cabinet,
			progress,
			get_open_info,
            COMPRESSION_TYPE))
		{
            (void) FCIDestroy(m_hfci);
			return FALSE;
		}
	return TRUE;
}

BOOL CCabinet::FlushCab()
{
	if (FALSE == FCIFlushCabinet(
		m_hfci,
		FALSE,
		get_next_cabinet,
		progress))
	{
        (void) FCIDestroy(m_hfci);
		return FALSE;
	}
    return FCIDestroy(m_hfci);
}

BOOL CCabinet::Compress(char *srcName, char *cabName)
{
	char	cab_name[MAX_PATH];

	if(srcName == NULL)
		return FALSE;
	if(cabName == NULL)
	{
		sprintf(cab_name, "%s.cab", srcName);
	}
	else
	{
		strcpy(cab_name, cabName);
	}
	if(CreateCabinet(cab_name)
		&& AddFile2Cab(srcName)
		&& FlushCab())
		return TRUE;
	else
		return FALSE;
}

BOOL CCabinet::Decompress(char *cabName, char *destPath)
{
	HFDI			hfdi;
	ERF				erf;
	FDICABINETINFO	fdici;
	int				hf;
	char			*p;
	char			cabinet_name[256];
	char			cabinet_path[256];

	if(cabName == NULL)
		return FALSE;

	hfdi = FDICreate(
		dmem_alloc,
		dmem_free,
		dfile_open,
		dfile_read,
		dfile_write,
		dfile_close,
		dfile_seek,
		cpu80386,
		&erf);

	if (hfdi == NULL)
	{
		return FALSE;
	}


	/*
	 * Is this file really a cabinet?
	 */
	hf = dfile_open(
		cabName,
		_O_BINARY | _O_RDONLY | _O_SEQUENTIAL,
		0
	);

	if (hf == -1)
	{
		(void) FDIDestroy(hfdi);
		return FALSE;
	}

	if (FALSE == FDIIsCabinet(
			hfdi,
			hf,
			&fdici))
	{
		_close(hf);
		(void) FDIDestroy(hfdi);
		return FALSE;
	}
	else
	{
		_close(hf);
	}

	p = strrchr(cabName, '\\');
	if (p == NULL)
	{
		strcpy(cabinet_name, cabName);
		strcpy(cabinet_path, "");
	}
	else
	{
		strcpy(cabinet_name, p+1);
		strncpy(cabinet_path, cabName, (int) (p-cabName)+1);
		cabinet_path[ (int) (p-cabName)+1 ] = '\0';
	}

	if(destPath == NULL)
		strcpy(dest_dir, cabinet_path);
	else
		strcpy(dest_dir, destPath);

	if (TRUE != FDICopy(
		hfdi,
		cabinet_name,
		cabinet_path,
		0,
		notification_function,
		NULL,
		NULL))
	{
		(void) FDIDestroy(hfdi);
		return FALSE;
	}

	if (FDIDestroy(hfdi) != TRUE)
	{
		return FALSE;
	}

	return TRUE;
}
