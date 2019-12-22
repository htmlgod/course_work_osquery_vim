BASEDIR=$(dirname "$0")
sh $BASEDIR/getConfigPath.sh
path=$(< path.txt)
grep "^set" ${path}
