#include <mpi.h>
#include <stdio.h>
int master(int procs){
    long matrixA[N][N], vectorC[N];
    long i,j,dotp, sender, row, numsent=0;
    MPI_Status status;
    /* Initialize data */
    for(i=0; i < N; i++)
    for(j=0; j < N; j++)
    matrixA[i][j] = 1;
    /* distribute data to slave */
    for(i=1; i < minFunc(procs, N); i++)
    { MPI_Send(&matrixA[i-1][0], N, MPI_LONG, i, i, MPI_COMM_WORLD ); } numsent++;
    /* receive result and distribute data */
    for(i=0; i < N; i++)
    { MPI_Recv(&dotp, 1, MPI_LONG, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status); /* SV xac dinh process gui ket qua ve va gui tiep du lieu cho no ??? */
        sender = status.MPI_SOURCE;
        row = status.MPI_TAG - 1;
        vectorC[row] = dotp;
        if(numsent < N) {
            MPI_Send(&matrixA[numsent][0], N, MPI_LONG, sender, numsent+1, MPI_COMM_WORLD);
        } numsent++;
        else {/* SV gui thong diep thong bao ket thuc cong viec */
            MPI_Send(MPI_BOTTOM, 0, MPI_LONG, sender, 0, MPI_COMM_WORLD); }}
    /* In ket qua de xac dinh tinh dung dan cua chuong trinh */
    for(i = 0; i < 10; i++)
    fprintf(stdout,"%ld ",vectorC[i]);
    return 0;
}
/* SV tìm hiểu mã nguồn chương trình và hoàn tất hàm slave */ int slave(){
    /* Cong viec cua slave */
    - Nhận dữ liệu từ master
    - Nhân vector dữ liệu vừa nhận với vector của nó
    - Gửi kết quả trả về
    - Đợi nhận thêm dữ liệu
    - Nếu không còn dữ liệu thì kết thúc
    /* Kết thúc */ return 0;
}
