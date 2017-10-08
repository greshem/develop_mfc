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
name => $name,
members=> \@members,
};


if ( ! -d  src_gen)
{
	mkdir("src_gen");
}


# ./tpl_sdk/name.h.tpl
# ./tpl_sdk/name.rc.tpl
# ./tpl_sdk/name.cpp.tpl

########################################################################
#resource

#app
$template->process("tpl_sdk/name.h.tpl", $vars, "src_gen/".$name.".h") || die $template->error();
$template->process("tpl_sdk/name.cpp.tpl", $vars, "src_gen/".$name.".cpp") || die $template->error();
#rc
$template->process("tpl_sdk/name.rc.tpl", $vars, "src_gen/".$name.".rc") || die $template->error();

########################################################################
 system("cp -a -r  tpl_sdk/GENERIC.ICO  src_gen/");
# system("cp -a tpl_dlg/StdAfx.h   src_gen/");
# system("cp -a tpl_dlg/StdAfx.cpp   src_gen/");
# system("cp -a one_step.bat src_gen/");

#chdir("src_gen");
#system("/bin/gen_makefile_from_file_latest.pl *.cpp");

