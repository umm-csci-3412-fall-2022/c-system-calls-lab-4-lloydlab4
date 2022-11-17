count=0
for file in $(find "$1" -type d)
do
    count=$((count+=1));
done
echo "There were $count directories."
c=0
for file in $(find "$1" -type f)
do
    co=$((co+=1));
done
echo "There were $co regular files."
