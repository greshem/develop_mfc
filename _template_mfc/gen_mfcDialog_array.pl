#!/usr/bin/perl
use Template;

my $config = {
INTERPOLATE  => 1,		      # expand "$var" in plain text
POST_CHOMP	  => 1,		      # cleanup whitespace
EVAL_PERL	  => 1,		      # evaluate Perl code blocks
};

my $template = Template->new();
#$name=shift  or die("Usage: $0 name\n");
$name=shift;
if(!defined($name))
{
	$name="RichTech_";
}

my $vars = {
Name => $name,
members=> \@members,
};


if ( ! -d  src_gen)
{
	mkdir("src_gen");
}

# tpl_dlg/Resource.h.tpl
# tpl_dlg/name.cpp.tpl
# tpl_dlg/name.h.tpl
# tpl_dlg/name.rc.tpl
# tpl_dlg/nameDlg.cpp.tpl
# tpl_dlg/nameDlg.h.tpl

########################################################################
#resource
$template->process("tpl_dlg/Resource.h.tpl", $vars, "src_gen/Resource.h") || die $template->error();
#app
$template->process("tpl_dlg/name.h.tpl", $vars, "src_gen/".$name.".h") || die $template->error();
$template->process("tpl_dlg/name.cpp.tpl", $vars, "src_gen/".$name.".cpp") || die $template->error();
#rc
$template->process("tpl_dlg/name.rc.tpl", $vars, "src_gen/".$name.".rc") || die $template->error();
#dlg
$template->process("tpl_dlg/nameDlg.cpp.tpl", $vars, "src_gen/".$name."Dlg.cpp") || die $template->error();
$template->process("tpl_dlg/nameDlg.h.tpl", $vars, "src_gen/".$name."Dlg.h") || die $template->error();

########################################################################
if ( -f "c:\\cygwin\\bin\\cp.exe")
{
	logger(" cygwin\\bin\\cp.exe 存在 用 linux cp.exe \n");
	system("cp -a -r  tpl_dlg/res/ src_gen/");
	system("cp -a tpl_dlg/StdAfx.h   src_gen/");
	system("cp -a tpl_dlg/StdAfx.cpp   src_gen/");
	system("cp -a one_step.bat src_gen/");
}
else
{
	logger(" cygwin\\bin\\cp.exe 不 存在 用 windows cmd.exe 的 copy.exe\n ");
	print ("xcopy /y /s  tpl_dlg\\res 		src_gen\\res");
	system("xcopy /y /s  tpl_dlg\\res 		src_gen\\res");
	system("copy /y  tpl_dlg\\StdAfx.h   	src_gen\\");
	system("copy /y  tpl_dlg\\StdAfx.cpp   	src_gen\\");
	system("copy /y  one_step.bat 			src_gen\\");
}

#chdir("src_gen");
#system("/bin/gen_makefile_from_file_latest.pl *.cpp");

sub logger($)
{
		(my $log_str)=@_;
		open(FILE, ">> all.log");
		print FILE $log_str;
		close(FILE);
}
