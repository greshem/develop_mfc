#include <afxwin.h>
#include <stdio.h> 

#include <windows.h>
#include<stdlib.h>
#include<stdio.h>


BOOL massid3lib_writeTitleTag(const char* file, const char title[]);
BOOL massid3lib_writeArtistTag(const char* file, const char artist[]);

int main(int argc,  char* argv[]) //main  for   console subsystem  
//winmain for  gui subsystem  
//int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR     lpCmdLine, int       nCmdShow)
{
	if(argc != 4)
	{
		printf("Usage: %s mp3_file  mp3_title   mp3_artist \n");
		printf("./%s  d:\\Abdc4vt.mp3 海底两万里   海底两万里作者\n", argv[0]);
		exit(-1);
	}
	srand( (unsigned)time( NULL ) ); 
	int number=rand();

	char file[1024];
	_snprintf(file, sizeof(file), "%s",  argv[1]);
	printf("mp3_file =%s\n", file);

	char title[1024];
	_snprintf(title, sizeof(title), "%s",  argv[2]);
	printf("title=%s\n", title);
	
	char artist[1024];
	_snprintf(artist, sizeof(artist), "%s", argv[3]);
	printf("artist=%s\n", artist);
	
	massid3lib_writeTitleTag(file, title);
	massid3lib_writeArtistTag(file, artist);
	return 0;
}

BOOL massid3lib_writeTitleTag(const char* file, const char title[])

{
        CFile mp3file;
        
        CString File = file;
        CString temp;
        temp = File.Right(4);
        if(temp == ".mp3" || temp == ".Mp3" || temp == ".mP3" || temp == ".MP3")
        {
                CFileStatus fstatus;
                mp3file.GetStatus(file, fstatus);
                if(fstatus.m_attribute != 0x20)
                {
                        fstatus.m_attribute = 0x20;
                        mp3file.SetStatus(file, fstatus);
                }
                mp3file.Open( file, CFile::modeReadWrite | CFile::typeBinary);
                mp3file.Seek( -125, CFile::end);

                long data[30] = {0};
                mp3file.Write(data, 30);
                
                if (title == "notitle")
                        {
                                mp3file.Close();
                        }
                else
                        {
                                CString str;
                                CString Title;
                                                                
                                str = title;
                                if(!str.IsEmpty())
                                {
                                        Title = str.Left(30);
                                        int bytes = Title.GetLength();

                                        mp3file.Seek( -125, CFile::end);                        
                                        mp3file.Write(LPCTSTR(Title), bytes);
                                        mp3file.Close();
                                }
                                else mp3file.Close();
                        }
        }
        return TRUE;
}

BOOL massid3lib_writeArtistTag(const char* file, const char artist[])
/* [<][>][^][v][top][bottom][index][help] */
{
        CFile mp3file;
        
        CString File = file;
        CString temp;
        temp = File.Right(4);
        if(temp == ".mp3" || temp == ".Mp3" || temp == ".mP3" || temp == ".MP3")
        {
                CFileStatus fstatus;
                mp3file.GetStatus(file, fstatus);
                if(fstatus.m_attribute != 0x20)
                {
                        fstatus.m_attribute = 0x20;
                        mp3file.SetStatus(file, fstatus);
                }
                mp3file.Open( file, CFile::modeReadWrite | CFile::typeBinary);
                mp3file.Seek( -95, CFile::end);

                long data[30] = {0};
                mp3file.Write(data, 30);
                
                if (artist == "noartist")
                        {
                                mp3file.Close();
                        }
                else
                        {
                                CString str;
                                CString Artist;
                                                                
                                str = artist;
                                if(!str.IsEmpty())
                                {
                                        Artist = str.Left(30);
                                        int bytes = Artist.GetLength();

                                        mp3file.Seek( -95, CFile::end);                 
                                        mp3file.Write(LPCTSTR(Artist), bytes);
                                        mp3file.Close();
                                }
                                else mp3file.Close();
                        }
                
        }
        return TRUE;
}

