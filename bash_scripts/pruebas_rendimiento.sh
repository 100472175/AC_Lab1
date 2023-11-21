rm numbers.txt
sbatch ejecuta.sh 100
for ((valor=500; valor<=4000; valor+=500))
do
  echo $valor >> numbers.txt
  sbatch ejecuta.sh 5 $valor | grep -oP '\b\d+\b' >> numbers.txt
  sleep 15
done
sleep 600
for ((valor=4500; valor<=5000; valor+=500))
do
  echo $valor >> numbers.txt
  sbatch ejecuta.sh 4 $valor | grep -oP '\b\d+\b' >> numbers.txt
  sleep 30
done
sleep 600
for ((valor=5500; valor<=6500; valor+=500))
do
  echo $valor >> numbers.txt
  sbatch ejecuta.sh 3 $valor | grep -oP '\b\d+\b' >> numbers.txt
  sleep 30
done
sleep 600
for ((valor=7000; valor<=10000; valor+=500))
do
  echo $valor >> numbers.txt
  sbatch ejecuta.sh 2 $valor | grep -oP '\b\d+\b' >> numbers.txt
  sleep 30
done
