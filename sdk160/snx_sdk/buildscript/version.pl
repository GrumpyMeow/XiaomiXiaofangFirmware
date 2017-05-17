#!/usr/bin/perl	-w
use	strict;

my $version_file = ">version.xls";
my $rootfs_folder = "../rootfs/lib/";

my $filename	= " ";
my $version	= " ";
my $license	= " ";
my $alias	= " ";
my $author	= " ";
my $description	= " ";
my $srcversion	= " ";
my $depends	= " ";
my $vermagic	= " ";
my $open_source	= "";


open(oFILE,$version_file) || die("Cannot Open $version_file: $!");

printf "Version	control	script\n";
my @modules= `ls $rootfs_folder/modules/2.6.35.12/kernel/drivers/`;
my @library= `ls $rootfs_folder`;

#printf oFILE "filename\tversion\talias\tlicense\tauthor\tdescription\tsrcversion\tdepends\tvermagic\n";
printf oFILE "filename\tversion\tlicense\tauthor\tdepends\tvermagic\n";

##############################
# parser library
##############################

    $open_source	= "$open_source libz.so.1";
#    $open_source	= "$open_source ";

#### middleware library (opne source)
    $open_source	= "$open_source libasound.so.2";
    $open_source	= "$open_source libblkid.so.1";	    #exfat
    $open_source	= "$open_source libntfs-3g.so.85";  #exfat
    $open_source	= "$open_source libuuid.so.1";	    #exfat
    $open_source	= "$open_source libSDL-1.2.so.0";
    $open_source	= "$open_source libssl.so.1.0.0";
    $open_source	= "$open_source libzbar.so.0";
    $open_source	= "$open_source libcrypto.so.1.0.0";#openssl
    $open_source	= "$open_source libcurl.so";	
    

#### Cross tool library (open source sysroot/lib)
#### Cross tool library (open source sysroot/usr/lib)
    $open_source	= "$open_source libgcc_s.so.1";
    $open_source	= "$open_source ld-uClibc.so.0";
    $open_source	= "$open_source libcrypt.so.0";
    $open_source	= "$open_source libc.so.0";
    $open_source	= "$open_source libdl.so.0";
    $open_source	= "$open_source libm.so.0";
#    $open_source	= "$open_source libnsl.so.0";
    $open_source	= "$open_source libpthread.so.0";
#    $open_source	= "$open_source libresolv.so.0";
    $open_source	= "$open_source librt.so.0";
    $open_source	= "$open_source libthread_db.so.1";
#    $open_source	= "$open_source libutil.so.0";
#
#    $open_source	= "$open_source libstdc++.so.6";
    $open_source	= "$open_source libstdc++*";

#### iptables
    $open_source	= "$open_source libxt_DSCP.so";
    $open_source	= "$open_source libxt_standard.so";
    $open_source	= "$open_source libxt_tcp.so";
    $open_source	= "$open_source libxt_udp.so";

#### tsocks
    $open_source	= "$open_source libtsocks.so";
    $open_source	= "$open_source libtsocks.so.1";
    $open_source	= "$open_source libtsocks.so.1.8";

#### galaxy server
    $open_source	= "$open_source libserverlog.so";
    $open_source	= "$open_source libxmllib.so";
#### web-admin
    $open_source	= "$open_source libisp.so";
    $open_source	= "$open_source libcodec_osd.so";
    $open_source	= "$open_source libsnxcgi.so";
#### modules
    $open_source	= "$open_source modules";

foreach	(@library) {
	my $this_line =	$_;
	if (($this_line	=~ /^\/\*/)||($this_line =~ /^\*/)||($this_line	=~ /^[\s]*$/)){
	    next;
	}
	chomp($this_line);
	my @value = split('.so', $this_line);
	if ($open_source =~ /$value[0]/) {
#	    print "open source library $this_line\n";
	    next;
	}
	
	my @readelf= `readelf -x .snx_version $rootfs_folder/$this_line`;
	$filename	= " ";
	$version	= " ";
	$license	= " ";
	$alias		= " ";
	$author		= " ";
	$description	= " ";
	$srcversion	= " ";
	$depends	= " ";
	$vermagic	= " ";

	my @test = split /\n/,$this_line;
	$filename= $test[0];

	if($#readelf =~	-1){
	    print oFILE "$filename\t$version\n";
	    next
	}
#        print "[$#readelf] @readelf";
    
    foreach	(@readelf) {
	my $this_line = $_;
        if (($this_line	=~ /^\/\*/)||($this_line =~	/^\*/)||($this_line =~ /^[\s]*$/)){
	    next;
	}
    
	my @line_array =	split /[\s]+/,$this_line;
	my $item = $line_array[$#line_array];
	if($item =~ /sn986/i){
	    $item = substr($item, 12);
	    my @last_array =    split /[\s]+/,$readelf[$#readelf-1];
	    $version ="$item$last_array[$#last_array]";
#	    print "$filename\t$version\n";
	    print oFILE "$filename\t$version\n";
	}
    }
}

##############################
# parser modules
##############################

foreach	(@modules) {
	my $this_line =	$_;
	if (($this_line	=~ /^\/\*/)||($this_line =~	/^\*/)||($this_line	=~ /^[\s]*$/)){
	    next;
	}
	my @info= `modinfo ../rootfs/lib/modules/2.6.35.12/kernel/drivers/$this_line`;

	$filename	= " ";
	$version	= " ";
	$license	= " ";
	$alias		= " ";
	$author		= " ";
	$description	= " ";
	$srcversion	= " ";
	$depends	= " ";
	$vermagic	= " ";
#	print @info;
	foreach	(@info)	{
		my $this_line =	$_;
		if (($this_line	=~ /^\/\*/)||($this_line =~	/^\*/)||($this_line	=~ /^[\s]*$/)){
			next;
		}
		my @line_array =	split /[\s]+/,$this_line;
		my $item = $line_array[0];
	
		if(($item =~ /^version:$/i) && ($#line_array >0)){
			$version = $line_array[1];
		}
		elsif(($item =~ /^filename:$/i) && ($#line_array >0)){
			$filename =	$line_array[1];
			my @folder =	split /\//,$filename;
			@folder=reverse(@folder);
			$filename =	$folder[0];
		}
		elsif(($item =~ /^alias:$/i) && ($#line_array >0)){
			$alias = $line_array[1];
		}
		elsif(($item =~ /^license:$/i) && ($#line_array >0)){
			$license = $line_array[1];
		}
		elsif(($item =~ /^author:$/i) && ($#line_array >0)){
			$author = $line_array[1];
		}
		elsif(($item =~ /^description:$/i) && ($#line_array >0)){
			$description = $line_array[1];
		}
		elsif(($item =~ /^srcversion:$/i) && ($#line_array >0)){
			$srcversion = $line_array[1];
		}
		elsif(($item =~ /^depends:$/i) && ($#line_array >0)){
			$depends = $line_array[1];
		}
		elsif($item =~ /^vermagic:$/i){
			$vermagic = $line_array[1];
		}
	}
#	printf "$filename\t$version\t$license\t$author\t$depends\t$vermagic\n";
	printf oFILE "$filename\t$version\t$license\t$author\t$depends\t$vermagic\n";
#	printf oFILE "$filename\t$version\t$alias\t$license\t$author\t$description\t$srcversion\t$depends\t$vermagic\n";
}


close(oFILE);
my $name_interrupt = "";
