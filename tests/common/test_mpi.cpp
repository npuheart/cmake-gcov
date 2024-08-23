// Author: Wes Kendall
// Copyright 2011 www.mpitutorial.com
// This code is provided freely with the tutorials on mpitutorial.com. Feel
// free to modify it for your own use. Any distribution of the code must
// either provide a link to www.mpitutorial.com or keep this header intact.

// Example using MPI_Send and MPI_Recv to pass a message around in a ring.

#include <mpi.h>
#include <spdlog/spdlog.h>
#include <stdio.h>
#include <stdlib.h>

int mpi_main() {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);
    // Find out rank, size
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int token;
    // Receive from the lower process and send to the higher process. Take
    // care of the special case when you are the first process to prevent
        // deadlock.
        if (world_rank != 0) {
        MPI_Recv(&token, 1, MPI_INT, world_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        spdlog::info("Process {0} received token {1} from process {2}", world_rank, token, world_rank - 1);
    }
    else {
        // Set the token's value if you are process 0
        token = -1;
    }
    token++;

    MPI_Send(&token, 1, MPI_INT, (world_rank + 1) % world_size, 0, MPI_COMM_WORLD);
    // Now process 0 can receive from the last process. This makes sure that
    // at least one MPI_Send is initialized before all MPI_Recvs (again, to
    // prevent deadlock)
    if (world_rank == 0) {
        MPI_Recv(&token, 1, MPI_INT, world_size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        spdlog::info("Process {0} received token {1} from process {2}", world_rank, token, world_size - 1);
    }
    MPI_Finalize();
    return 0;
}
