#!/usr/bin/perl
use strict;
use warnings;
use lib '/home/marui/perl/test';
use SimpleTrie;
use SimpleHash;
use Time::HiRes qw/gettimeofday tv_interval/; 

my $trial = shift;
my $data = shift;

my $trie = SimpleTrie::SimpleTrie->new;
#ハッシュの大きさは1億としておく。(リハッシュできないため)
my $hash = SimpleHash::SimpleHash->new(10000000);
my %phash;

my $incr_st = sub {
    my $key = shift;
    $trie->increment($key);
};

my $incr_sh = sub {
    my $key = shift;
    $hash->increment($key);
};

my $incr_ph = sub {
    my $key = shift;
    $phash{$key}++;
};

print count_word($data,$incr_st),"\t";
print count_word($data,$incr_sh),"\t";
print count_word($data,$incr_ph),"\n";

#print scalar keys %phash,"\n";
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
