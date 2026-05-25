#!/bin/sh
# termfilechooser wrapper with a working "save" flow.
#
# Open/upload selections fall through to the stock yazi-wrapper. Saving is the
# special case: yazi can't "select" a file that doesn't exist yet, so instead
# the user navigates to the destination folder and we capture yazi's cwd on
# exit (--cwd-file), then append the application's suggested filename.
#
# Inside yazi: navigate normally, or press Z to fuzzy-jump to a folder with
# fzf, then press q to confirm.
set -eu

multiple=$1
directory=$2
save=$3
path=$4
out=$5
loglevel=$6

stock=/usr/share/xdg-desktop-portal-termfilechooser/yazi-wrapper.sh
termcmd=${TERMCMD:-kitty --title termfilechooser}

if [ "$save" != 1 ]; then
	exec "$stock" "$multiple" "$directory" "$save" "$path" "$out" "$loglevel"
fi

name=$(basename -- "$path")
case $name in
	"" | . | .. | /) name=download ;;
esac

start=$path
[ -d "$start" ] || start=$(dirname -- "$path")
[ -d "$start" ] || start=${XDG_DOWNLOAD_DIR:-$HOME/Downloads}
[ -d "$start" ] || start=$HOME

cwdfile=$(mktemp "${TMPDIR:-/tmp}/xdptf-cwd.XXXXXX")
trap 'rm -f "$cwdfile"' EXIT INT TERM

$termcmd yazi --cwd-file="$cwdfile" "$start"

[ -s "$cwdfile" ] || exit 1
dir=$(cat "$cwdfile")
[ -d "$dir" ] || exit 1

printf '%s/%s\n' "$dir" "$name" >"$out"
