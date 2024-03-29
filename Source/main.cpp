
#include <iostream>

#include <AMReX.H>
#include <AMReX_ParmParse.H>
#include <AMReX_BLProfiler.H>
#include <AMReX_ParallelDescriptor.H>

#include <WarpX.H>
#include <WarpXUtil.H>

#include "perf_dump.h"

using namespace amrex;

int main(int argc, char* argv[])
{
#if defined(_OPENMP) && defined(WARPX_USE_PSATD)
    int provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);
    assert(provided >= MPI_THREAD_FUNNELED);
#else
    MPI_Init(&argc, &argv);
#endif

    amrex::Initialize(argc,argv);

    ConvertLabParamsToBoost();

    BL_PROFILE_VAR("main()", pmain);
pdump_start_region_with_name( "main()"  );
pdump_start_profile();
        
    const Real strt_total = amrex::second();

    {
	WarpX warpx;
	
	warpx.InitData();

	warpx.Evolve();
	
	Real end_total = amrex::second() - strt_total;
	
	ParallelDescriptor::ReduceRealMax(end_total ,ParallelDescriptor::IOProcessorNumber());
	if (warpx.Verbose()) {
            amrex::Print() << "Total Time                     : " << end_total << '\n';
            amrex::Print() << "WarpX Version: " << WarpX::Version() << '\n';
            amrex::Print() << "PICSAR Version: " << WarpX::PicsarVersion() << '\n';
	}
    }

    BL_PROFILE_VAR_STOP(pmain);

    amrex::Finalize();
pdump_end_profile();
pdump_end_region();
    MPI_Finalize();
}
