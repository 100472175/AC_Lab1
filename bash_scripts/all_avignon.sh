
rm -rf slurm*
sbatch compila.sh
sleep 40
job_id_fluid=$(sbatch ejecuta.sh | awk '{print $4}')
echo "Submitted batch job $job_id_fluid"
sleep 1
tail -f *$job_id_fluid* &

# Hay que ver si esto funciona bien o no, estaría bien que si