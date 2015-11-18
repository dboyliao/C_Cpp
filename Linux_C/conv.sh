. ~/.bash_profile

for file in $( ls . )
do
    if [ file != "conv.sh" ];
    then
        iconv_inplace big5 utf-8 $file
    fi
done
