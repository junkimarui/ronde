#!/usr/bin/perl
use strict;
use warnings;
use Time::HiRes qw/gettimeofday tv_interval/;

my $list_file = "textlist.perl";
my %data = %{eval(`cat $list_file`)};
my $trial = 20;

my %programs = (perl => "perl count.pl", cpp => "./count");

for my $key (sort {$a cmp $b} keys %data) {
    for my $program (keys %programs) {
	for (my $i = 1; $i <= $trial; $i++) {
	    print $key,"\t",$program,"\t",$i,"\t";
	    print `$programs{$program} $i $data{$key}`;
	}
    }
}

