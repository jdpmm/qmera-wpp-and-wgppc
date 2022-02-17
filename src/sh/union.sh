#! /bin/sh

touch "$1.s"
cat "data.s" >> "$1.s"
cat "code.s" >> "$1.s"

rm code.s
rm data.s
mv "$1.s" out/
echo "Well done, no error reported"
