#!/usr/bin/perl
use strict;
use warnings;
use Time::HiRes qw/gettimeofday tv_interval/;

my $list_file = "../textlist.perl";
my %data = %{eval(`cat $list_file`)};
my $trial = 5;

my %programs = (xs => "perl count.pl");

for my $key (sort {$a cmp $b} keys %data) {
    for my $program (keys %programs) {
	for (my $i = 1; $i <= $trial; $i++) {
	    print $key,"\t",$program,"\t",$i,"\t";
	    print `$programs{$program} $i $data{$key}`;
	}
    }
}

