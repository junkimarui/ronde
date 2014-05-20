#!/usr/bin/perl
use strict;
use warnings;
use FindBin;
use ExtUtils::testlib;
use SimpleHashXS;
use Time::HiRes qw/gettimeofday tv_interval/; 

my $trial = shift;
my $data = shift;

#Hashの大きさを1億に。(リハッシュできないため)
SimpleHashXS::init(100000000);

my $incr_st = sub {
    my $key = shift;
    SimpleHashXS::increment($key);
};

print count_word($data,$incr_st),"\n";

sub count_word {
    my $file = shift;
    my $incr = shift;
    my $t0 = [gettimeofday];
    open(my $fh,"<",$file);
    while (my $l = <$fh>) {
	chomp($l);
	my @k = split(" ",$l);
	for my $elm (@k) {
	    $incr->($elm);
	}
    }
    close($fh);
    my $t1 = [gettimeofday];
    my $execTime = tv_interval($t0,$t1);
    return $execTime;
}
