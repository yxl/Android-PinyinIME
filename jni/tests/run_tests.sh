# !/bin/sh

echo "Make ..."
make

echo "Run tests .."
LIST="a b c d e f g h z ba da fa ga ha"
for i in $LIST
do
  echo "run 10000 times for $i:"
  ./pinyinime_dictbuilder $i no-details
done

