cmd_find.pl mfc
c:\bin\compile_console.pl
gen_bakefile_bkl.pl
bakefile -f msvc  build.bkl

nmake /f makefile.vc
