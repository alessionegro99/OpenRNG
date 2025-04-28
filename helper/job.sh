#!/bin/bash
#SBATCH --account=training2507
#SBATCH --time=00:20:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --partition=dc-cpu-devel
#SBATCH --cpus-per-task=256
#SBATCH --threads-per-core=2
#SBATCH --job-name=02_stream_omp

echo "Job start: " $(date)
module list 2>&1
printf "Run: Node: $SLURMD_NODENAME ; ntasks: $SLURM_NTASKS \n"
echo "Node cabinets and electric groups"
scontrol show nodes ${SLURM_JOB_NODELIST} | grep -i activefeatures | sort -u
echo

sizes=( 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288
        1048576 2097152 4194304 8388608 16777216 33554432 67108864
        134217728 268435456 )

for nt in 1 2 4 8 16 32 64 128 256; do
  for places in cores threads; do
    for bnd in close spread; do
      for sz in ${sizes[@]}; do
        echo nt=$nt places=$places bnd=$bnd sz=$sz
        log=results/NT${nt}_PLACES${places}_BIND${bnd}_SIZE${sz}.out
        OMP_NUM_THREADS=$nt OMP_PLACES=$places OMP_PROC_BIND=$bnd ./stream $sz | tee ${log}
        echo
      done
    done
  done
done

echo "Job end: " $(date)

