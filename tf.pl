#!/usr/bin/perl
use strict;
use warnings;
use lib '/home/marui/perl/test';
use SimpleTrie;
use SimpleHash;
use Time::HiRes qw/gettimeofday tv_interval/; 

die "Usage: perl tf.pl [container type] [file]\n" if ($#ARGV < 1);

my $container = shift;
my $data = shift;
my $outfile = $data.".tf";

my $trie = SimpleTrie::SimpleTrie->new;
#ハッシュの大きさは1億としておく。(リハッシュできないため)
my $hash = SimpleHash::SimpleHash->new(10000000);
my %phash;

my $incr_st = sub {
    my $key = shift;
    $trie->increment($key);
};
my $vsort_st = sub {
    return $trie->keyValSorted;
};

my $incr_sh = sub {
    my $key = shift;
    $hash->increment($key);
};
my $vsort_sh = sub {
    return $hash->keyValSorted;
};

my $incr_ph = sub {
    my $key = shift;
    $phash{$key}++;
};
my $vsort_ph = sub {
    my @sorted_keys = sort {$phash{$b} <=> $phash{$a}} keys %phash;
    return \@sorted_keys;
};

if ($container eq "t") {
    print STDERR count_word($data,$incr_st,$vsort_st),"\n";
}
elsif ($container eq "h") {
    print STDERR count_word($data,$incr_sh,$vsort_sh),"\n";
}
else {
    print STDERR count_word($data,$incr_ph,$vsort_ph),"\n";
}

#print scalar keys %phash,"\n";
sub count_word {
    my $file = shift;
    my $incr = shift;
    my $vsort = shift;
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
    my $dump = $vsort->();
    my $t1 = [gettimeofday];
    my $execTime = tv_interval($t0,$t1);
    open (my $ofh, ">", $outfile);
    if ($container eq "t" || $container eq "h") {
	for my $pair (@{$dump}) {
	    print $ofh $pair->getFirst,"\t",$pair->getSecond,"\n";
	}
    }
    else {
	for my $key (@{$dump}) {
	    print $ofh $key,"\t",$phash{$key},"\n";
	} 
    }
    close($ofh);
    return $execTime;
}
