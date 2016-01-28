PNAME=`echo "$2" | sed -e 's/\//./g'`

find $2 -name "*.?pp" -exec licenseAdder -n $1 -t cpp -p $PNAME -f {} \;
find $2 -name "*.xml" -exec licenseAdder -n $1 -t xml -p $PNAME -f {} \;

