#!/usr/bin/perl
use strict;
use warnings;
use Time::HiRes qw/gettimeofday tv_interval/;

my %data = ("3_tw10M" => "/large_data/twitter_data/tweets10M.wakati",
	    "4_tw25M" => "/large_data/twitter_data/tweets25M.wakati",
	    "5_tw50M" => "/large_data/twitter_data/tweets50M.wakati",
	    "6_tw75M" => "/large_data/twitter_data/tweets75M_2.wakati",
	    "7_tw" => "/large_data/twitter_data/age_all_tweets.csv.wakati",
	    "8_wikip" => "/large_data/wikipedia_ja/article_all.wakati",
	    "1_nikkei" => "/large_data/nikkei/2012_wakati.txt",
	    "2_aozora" => "/large_data/aozora/doc_wakati.txt"
    );
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

