FILENAME=$1
EXT=${FILENAME#*.}

case "$EXT" in
	"Z")
		uncompress $FILENAME
		;;
	"gz")
		gunzip $FILENAME
		;;
	"tar")
		tar -xvf $FILENAME
		;;
	"tar.gz")
		tar -zxvf $FILENAME
		;;
	"tar.bz2")
		tar -jxvf $FILENAME
		;;
	"tar.Z")
		tar -Zxvf $FILENAME
		;;
	"rar")
		unrar e $FILENAME
		;;
	"zip")
		unzip $FILENAME
		;;
	*)
		echo "unknown file format"
		;;
esac