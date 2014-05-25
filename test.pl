#!/usr/bin/perl
use strict;
use warnings;
use lib '/home/marui/perl/test';
use SimpleTrie;
use SimpleHash;
use Time::HiRes qw/gettimeofday tv_interval/; 
use Data::Dumper;

my $trie = SimpleTrie::SimpleTrie->new;
my $hash = SimpleHash::SimpleHash->new;
my $t0 = [gettimeofday];
$trie->set("abc",2);
$trie->set("abcd",3);
$trie->increment("あべこべ");
my $t1 = [gettimeofday];
print $trie->get("abc"),"\n";
print $trie->get("abcd"),"\n";
print $trie->get("あべこべ"),"\n";
$trie->increment("abcクッキングスタジオ");
$trie->increment("a");

my $it = $trie->prefix_search("");
while (my $elm = $it->next) {
    print $elm,"\n";
}
print $trie->toString;
my $execTime = tv_interval($t0,$t1);
print "exec time:",$execTime,"\n";

$hash->set("abcd",2);
$hash->set("abc",3);
$hash->increment("abd");
$hash->increment("abc");
print $hash->get("abcd"),"\n";
print $hash->get("abc"),"\n";
print $hash->get("あべこべ"),"\n";
print $hash->toString;
my $obj = $trie->common_prefix_search("abcクッキングスタジオに行きたい");
for my $o (@$obj) {
    print $o,"\n";
} 
