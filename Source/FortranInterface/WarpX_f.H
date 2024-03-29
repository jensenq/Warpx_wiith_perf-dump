
#include <AMReX_BLFort.H>

#ifdef __cplusplus

#if AMREX_SPACEDIM==2
#define WARPX_ARLIM_ANYD(x) std::array<int,3>{(x)[0], 0, (x)[1]}.data()
#else
#define WARPX_ARLIM_ANYD(x) x
#endif

#define WARPX_TO_FORTRAN_BOX(x) WARPX_ARLIM_ANYD((x).loVect()), WARPX_ARLIM_ANYD((x).hiVect())
#define WARPX_TO_FORTRAN_ANYD(x) (x).dataPtr(), WARPX_ARLIM_ANYD((x).loVect()), WARPX_ARLIM_ANYD((x).hiVect())
#define WARPX_TO_FORTRAN_N_ANYD(x,n) (x).dataPtr(n), WARPX_ARLIM_ANYD((x).loVect()), WARPX_ARLIM_ANYD((x).hiVect())

#endif

#if (AMREX_SPACEDIM == 3)

#define WRPX_COMPUTE_DIVB                warpx_compute_divb_3d
#define WRPX_COMPUTE_DIVE                warpx_compute_dive_3d
#define WRPX_SYNC_CURRENT                warpx_sync_current_3d
#define WRPX_SYNC_RHO                    warpx_sync_rho_3d

#define WRPX_PUSH_PML_BVEC               warpx_push_pml_bvec_3d
#define WRPX_PUSH_PML_EVEC               warpx_push_pml_evec_3d
#define WRPX_PUSH_PML_EVEC_F             warpx_push_pml_evec_f_3d
#define WRPX_PUSH_PML_F                  warpx_push_pml_f_3d
#define WRPX_DAMP_PML                    warpx_damp_pml_3d
#define WRPX_DAMP_PML_F                  warpx_damp_pml_f_3d

#define WRPX_SUM_FINE_TO_CRSE_NODAL      warpx_sum_fine_to_crse_nodal_3d
#define WRPX_ZERO_OUT_BNDRY              warpx_zero_out_bndry_3d
#define WRPX_BUILD_MASK                  warpx_build_mask_3d
#define WRPX_COMPUTE_E_NODAL             warpx_compute_E_nodal_3d
#define WRPX_DEPOSIT_CIC                 warpx_deposit_cic_3d
#define WRPX_INTERPOLATE_CIC             warpx_interpolate_cic_3d
#define WRPX_INTERPOLATE_CIC_TWO_LEVELS  warpx_interpolate_cic_two_levels_3d
#define WRPX_PUSH_LEAPFROG               warpx_push_leapfrog_3d
#define WRPX_PUSH_LEAPFROG_POSITIONS     warpx_push_leapfrog_positions_3d

#elif (AMREX_SPACEDIM == 2)

#define WRPX_COMPUTE_DIVB                warpx_compute_divb_2d
#define WRPX_SYNC_CURRENT                warpx_sync_current_2d
#define WRPX_SYNC_RHO                    warpx_sync_rho_2d

#define WRPX_PUSH_PML_BVEC               warpx_push_pml_bvec_2d
#define WRPX_PUSH_PML_EVEC               warpx_push_pml_evec_2d
#define WRPX_PUSH_PML_EVEC_F             warpx_push_pml_evec_f_2d
#define WRPX_PUSH_PML_F                  warpx_push_pml_f_2d
#define WRPX_DAMP_PML                    warpx_damp_pml_2d
#define WRPX_DAMP_PML_F                  warpx_damp_pml_f_2d

#define WRPX_SUM_FINE_TO_CRSE_NODAL      warpx_sum_fine_to_crse_nodal_2d
#define WRPX_ZERO_OUT_BNDRY              warpx_zero_out_bndry_2d
#define WRPX_BUILD_MASK                  warpx_build_mask_2d
#define WRPX_COMPUTE_E_NODAL             warpx_compute_E_nodal_2d
#define WRPX_DEPOSIT_CIC                 warpx_deposit_cic_2d
#define WRPX_INTERPOLATE_CIC             warpx_interpolate_cic_2d
#define WRPX_INTERPOLATE_CIC_TWO_LEVELS  warpx_interpolate_cic_two_levels_2d
#define WRPX_PUSH_LEAPFROG               warpx_push_leapfrog_2d
#define WRPX_PUSH_LEAPFROG_POSITIONS     warpx_push_leapfrog_positions_2d

#ifdef WARPX_RZ
#define WRPX_COMPUTE_DIVE                warpx_compute_dive_rz
#else
#define WRPX_COMPUTE_DIVE                warpx_compute_dive_2d
#endif

#endif

#ifdef __cplusplus
extern "C"
{
#endif

    void warpx_copy_attribs(const long* np,
                            const amrex_real* xp, const amrex_real* yp, const amrex_real* zp,
                            const amrex_real* uxp, const amrex_real* uyp, const amrex_real* uzp,
                            amrex_real* xpold, amrex_real* ypold, amrex_real* zpold,
                            amrex_real* uxpold, amrex_real* uypold, amrex_real* uzpold);

	// Charge deposition
	void warpx_charge_deposition(amrex::Real* rho,
            const long* np,	const amrex::Real* xp, const amrex::Real* yp, const amrex::Real* zp,	const amrex::Real* w,
			const amrex::Real* q, const amrex::Real* xmin, const amrex::Real* ymin, const amrex::Real* zmin,
			const amrex::Real* dx, const amrex::Real* dy, const amrex::Real* dz,
			const long* nx, const long* ny, const long* nz,
			const long* nxguard, const long* nyguard, const long* nzguard,
			const long* nox, const long* noy,const long* noz,
			const long* lvect, const long* charge_depo_algo);

        // Charge deposition finalize for RZ
        void warpx_charge_deposition_rz_volume_scaling(
			amrex::Real* rho, const long* rho_ng, const int* rho_ntot,
			const amrex::Real* rmin,
			const amrex::Real* dr);

	// Current deposition
	void warpx_current_deposition(
			amrex::Real* jx, const long* jx_ng, const int* jx_ntot,
			amrex::Real* jy, const long* jy_ng, const int* jy_ntot,
			amrex::Real* jz, const long* jz_ng, const int* jz_ntot,
			const long* np,
			const amrex::Real* xp, const amrex::Real* yp, const amrex::Real* zp,
			const amrex::Real* uxp, const amrex::Real* uyp,const amrex::Real* uzp,
			const amrex::Real* gip, const amrex::Real* w, const amrex::Real* q,
			const amrex::Real* xmin, const amrex::Real* ymin, const amrex::Real* zmin,
			const amrex::Real* dt,
			const amrex::Real* dx, const amrex::Real* dy, const amrex::Real* dz,
			const long* nox, const long* noy,const long* noz,
                        const int* l_nodal, const long* lvect, const long* current_depo_algo);

        // Current deposition finalize for RZ
        void warpx_current_deposition_rz_volume_scaling(
			amrex::Real* jx, const long* jx_ng, const int* jx_ntot,
			amrex::Real* jy, const long* jy_ng, const int* jy_ntot,
			amrex::Real* jz, const long* jz_ng, const int* jz_ntot,
			const amrex::Real* rmin,
			const amrex::Real* dr);

	// Field gathering

	void warpx_geteb_energy_conserving(const long* np,
			const amrex::Real* xp, const amrex::Real* yp, const amrex::Real* zp,
			amrex::Real* exp, amrex::Real* eyp, amrex::Real* ezp,
                        amrex::Real* bxp, amrex::Real* byp, amrex::Real* bzp,
                        const int* ixyzmin,
                        const amrex::Real* xmin, const amrex::Real* ymin, const amrex::Real* zmin,
                        const amrex::Real* dx, const amrex::Real* dy, const amrex::Real* dz,
			const long* nox, const long* noy, const long* noz,
			const amrex::Real* exg, const int* exg_lo, const int* exg_hi,
			const amrex::Real* eyg, const int* eyg_lo, const int* eyg_hi,
			const amrex::Real* ezg, const int* ezg_lo, const int* ezg_hi,
			const amrex::Real* bxg, const int* bxg_lo, const int* bxg_hi,
			const amrex::Real* byg, const int* byg_lo, const int* byg_hi,
			const amrex::Real* bzg, const int* bzg_lo, const int* bzg_hi,
			const int* ll4symtry, const int* l_lower_order_in_v,
                        const int* l_nodal, const long* lvect,
			const long* field_gathe_algo);

	// Particle pusher (velocity and position)

	void warpx_particle_pusher(const long* np,
			amrex::Real* xp, amrex::Real* yp, amrex::Real* zp,
			amrex::Real* uxp, amrex::Real* uyp, amrex::Real* uzp, amrex::Real* gaminv,
			const amrex::Real* exp, const amrex::Real* eyp,const amrex::Real* ezp,
			const amrex::Real* bxp, const amrex::Real* byp,const amrex::Real* bzp,
			const amrex::Real* charge, const amrex::Real* mass, const amrex::Real* dt,
			const long* particle_pusher_algo);

	// Particle pusher (velocity)

	void warpx_particle_pusher_momenta(const long* np,
			amrex::Real* xp, amrex::Real* yp, amrex::Real* zp,
			amrex::Real* uxp, amrex::Real* uyp, amrex::Real* uzp, amrex::Real* gaminv,
			const amrex::Real* exp, const amrex::Real* eyp,const amrex::Real* ezp,
			const amrex::Real* bxp, const amrex::Real* byp,const amrex::Real* bzp,
			const amrex::Real* charge, const amrex::Real* mass, const amrex::Real* dt,
			const long* particle_pusher_algo);


    // Laser pusher

	void warpx_gaussian_laser( const long* np,
				amrex::Real* Xp, amrex::Real* Yp, amrex::Real* t, amrex::Real* wavelength, amrex::Real* e_max, amrex::Real* waist,
				amrex::Real* duration, amrex::Real* t_peak, amrex::Real* f, amrex::Real* amplitude,
				amrex::Real* zeta, amrex::Real* beta, amrex::Real* phi2, amrex::Real* theta_stc );

        void warpx_harris_laser( const long* np,
                                 amrex::Real* Xp, amrex::Real* Yp, amrex::Real* t, amrex::Real* wavelength,
                                 amrex::Real* e_max, amrex::Real* waist, amrex::Real* duration, amrex::Real* f, amrex::Real* amplitude );

  void calculate_laser_plane_coordinates( const long* np,
       amrex::Real* xp, amrex::Real* yp, amrex::Real* zp,
       amrex::Real* plane_Xp, amrex::Real* plane_Yp,
       amrex::Real* u_Xx, amrex::Real* u_Xy, amrex::Real* u_Xz,
       amrex::Real* u_Yx, amrex::Real* u_Yy, amrex::Real* u_Yz,
       amrex::Real* positionx, amrex::Real* positiony, amrex::Real* positionz );

  void update_laser_particle( const long* np,
       amrex::Real* xp, amrex::Real* yp, amrex::Real* zp,
       amrex::Real* uxp, amrex::Real* uyp, amrex::Real* uzp,
       amrex::Real* giv, amrex::Real* wp, amrex::Real* amplitude_E,
       amrex::Real* p_Xx, amrex::Real* p_Xy, amrex::Real* p_Xz,
       amrex::Real* nvecx, amrex::Real* nvecy, amrex::Real* nvecz,
       amrex::Real* mobility, amrex::Real* dt,  const amrex::Real* c,
       const amrex::Real* beta_boost, const amrex::Real* gamma_boost );

    // Maxwell solver

        void warpx_push_evec(
                const int* xlo, const int* xhi,
                const int* ylo, const int* yhi,
                const int* zlo, const int* zhi,
                BL_FORT_FAB_ARG_3D(ex),
                BL_FORT_FAB_ARG_3D(ey),
                BL_FORT_FAB_ARG_3D(ez),
                const BL_FORT_FAB_ARG_3D(bx),
                const BL_FORT_FAB_ARG_3D(by),
                const BL_FORT_FAB_ARG_3D(bz),
                const BL_FORT_FAB_ARG_3D(jx),
                const BL_FORT_FAB_ARG_3D(jy),
                const BL_FORT_FAB_ARG_3D(jz),
                const amrex::Real* mudt,
                const amrex::Real* dtsdx,
                const amrex::Real* dtsdy,
                const amrex::Real* dtsdz,
                const amrex::Real* xmin,
                const amrex::Real* dx);

        void warpx_push_bvec(
                const int* xlo, const int* xhi,
                const int* ylo, const int* yhi,
                const int* zlo, const int* zhi,
                const BL_FORT_FAB_ARG_3D(ex),
                const BL_FORT_FAB_ARG_3D(ey),
                const BL_FORT_FAB_ARG_3D(ez),
                BL_FORT_FAB_ARG_3D(bx),
                BL_FORT_FAB_ARG_3D(by),
                BL_FORT_FAB_ARG_3D(bz),
                const amrex::Real* dtsdx,
                const amrex::Real* dtsdy,
                const amrex::Real* dtsdz,
                const amrex::Real* xmin,
                const amrex::Real* dx,
		const int* maxwell_fdtd_solver_id);

        void warpx_push_evec_f(
                const int* xlo, const int* xhi,
                const int* ylo, const int* yhi,
                const int* zlo, const int* zhi,
                BL_FORT_FAB_ARG_3D(ex),
                BL_FORT_FAB_ARG_3D(ey),
                BL_FORT_FAB_ARG_3D(ez),
                const BL_FORT_FAB_ARG_3D(f),
                const amrex::Real* dtsdx_c2,
                const amrex::Real* dtsdy_c2,
                const amrex::Real* dtsdz_c2,
		const int* maxwell_fdtd_solver_id);

#ifdef USE_OPENBC_POISSON
    void warpx_openbc_potential (amrex::Real* rho, amrex::Real* phi, const amrex::Real* dx);
    void warpx_openbc_decompose (const int*, const int*, int*, int*);
#endif

    void warpx_compute_E (const int* lo, const int* hi,
			  const BL_FORT_FAB_ARG_3D(phi),
			  BL_FORT_FAB_ARG_3D(Ex),
			  BL_FORT_FAB_ARG_3D(Ey),
			  BL_FORT_FAB_ARG_3D(Ez),
			  const amrex::Real* dx);

///
/// These functions are used in electrostatic mode.
///

    void WRPX_SUM_FINE_TO_CRSE_NODAL(const int* lo, const int* hi, const int* lrat,
                                     amrex::Real* crse, const int* clo, const int* chi,
                                     const amrex::Real* fine, const int* flo, const int* fhi);

    void WRPX_ZERO_OUT_BNDRY(const int* lo, const int* hi,
                             amrex::Real* input_data, amrex::Real* bndry_data,
                             const int* mask);

    void WRPX_BUILD_MASK(const int* lo, const int* hi,
                         const int* tmp_mask, int* mask, const int* ncells);

    void WRPX_COMPUTE_E_NODAL(const int* lo, const int* hi,
                              const amrex::Real* phi,
                              amrex::Real* Ex, amrex::Real* Ey,
#if (AMREX_SPACEDIM == 3)
                          amrex::Real* Ez,
#endif
                          const amrex::Real* dx);

    void WRPX_DEPOSIT_CIC(const amrex::Real* particles, int ns, int np,
                          const amrex::Real* weights,
                          const amrex::Real* charge,
                          amrex::Real* rho, const int* lo, const int* hi,
                          const amrex::Real* plo, const amrex::Real* dx,
                          const int* ng);

    void WRPX_INTERPOLATE_CIC_TWO_LEVELS(const amrex::Real* particles, int ns, int np,
                                         amrex::Real* Ex_p, amrex::Real* Ey_p,
#if (AMREX_SPACEDIM == 3)
                                         amrex::Real* Ez_p,
#endif
                                         const amrex::Real* Ex, const amrex::Real* Ey,
#if (AMREX_SPACEDIM == 3)
                                         const amrex::Real* Ez,
#endif
                                         const int* lo, const int* hi, const amrex::Real* dx,
                                         const amrex::Real* cEx, const amrex::Real* cEy,
#if (AMREX_SPACEDIM == 3)
                                         const amrex::Real* cEz,
#endif
                                         const int* mask,
                                         const int* clo, const int* chi, const amrex::Real* cdx,
                                         const amrex::Real* plo, const int* ng, const int* lev);

    void WRPX_INTERPOLATE_CIC(const amrex::Real* particles, int ns, int np,
                              amrex::Real* Ex_p, amrex::Real* Ey_p,
#if (AMREX_SPACEDIM == 3)
                              amrex::Real* Ez_p,
#endif
                              const amrex::Real* Ex, const amrex::Real* Ey,
#if (AMREX_SPACEDIM == 3)
                              const amrex::Real* Ez,
#endif
                              const int* lo, const int* hi,
                              const amrex::Real* plo, const amrex::Real* dx,
                              const int* ng);

    void WRPX_PUSH_LEAPFROG(amrex::Real* particles, int ns, int np,
                            amrex::Real* vx_p, amrex::Real* vy_p,
#if (AMREX_SPACEDIM == 3)
                            amrex::Real* vz_p,
#endif
                            const amrex::Real* Ex_p, const amrex::Real* Ey_p,
#if (AMREX_SPACEDIM == 3)
                            const amrex::Real* Ez_p,
#endif
                            const amrex::Real* charge, const amrex::Real* mass, const amrex::Real* dt,
                            const amrex::Real* prob_lo, const amrex::Real* prob_hi);

    void WRPX_PUSH_LEAPFROG_POSITIONS(amrex::Real* particles, int ns, int np,
                                      amrex::Real* vx_p, amrex::Real* vy_p,
#if (AMREX_SPACEDIM == 3)
                                      amrex::Real* vz_p,
#endif
                                      const amrex::Real* dt, const amrex::Real* prob_lo,
                                      const amrex::Real* prob_hi);

//  These functions are used to evolve E and B in the PML

    void WRPX_COMPUTE_DIVB (const int* lo, const int* hi,
                             BL_FORT_FAB_ARG_ANYD(divb),
                             const BL_FORT_FAB_ARG_ANYD(Bx),
                             const BL_FORT_FAB_ARG_ANYD(By),
                             const BL_FORT_FAB_ARG_ANYD(Bz),
                             const amrex::Real* dx);

    void WRPX_COMPUTE_DIVE (const int* lo, const int* hi,
                             BL_FORT_FAB_ARG_ANYD(dive),
                             const BL_FORT_FAB_ARG_ANYD(ex),
                             const BL_FORT_FAB_ARG_ANYD(ey),
                             const BL_FORT_FAB_ARG_ANYD(ez),
                             const amrex::Real* dx
#ifdef WARPX_RZ
                             ,const amrex::Real* rmin
#endif
                             );

    void WRPX_PUSH_PML_BVEC(const int* xlo, const int* xhi,
                            const int* ylo, const int* yhi,
                            const int* zlo, const int* zhi,
                            const BL_FORT_FAB_ARG_3D(ex),
                            const BL_FORT_FAB_ARG_3D(ey),
                            const BL_FORT_FAB_ARG_3D(ez),
                            BL_FORT_FAB_ARG_3D(bx),
                            BL_FORT_FAB_ARG_3D(by),
                            BL_FORT_FAB_ARG_3D(bz),
                            const amrex::Real* dtsdx,
			    const amrex::Real* dtsdy,
			    const amrex::Real* dtsdz,
			    const int* maxwell_fdtd_solver_id);


    void WRPX_PUSH_PML_EVEC(const int* xlo, const int* xhi,
                            const int* ylo, const int* yhi,
                            const int* zlo, const int* zhi,
                            BL_FORT_FAB_ARG_3D(ex),
                            BL_FORT_FAB_ARG_3D(ey),
                            BL_FORT_FAB_ARG_3D(ez),
                            const BL_FORT_FAB_ARG_3D(bx),
                            const BL_FORT_FAB_ARG_3D(by),
                            const BL_FORT_FAB_ARG_3D(bz),
                            const amrex::Real* dtsdx,
                            const amrex::Real* dtsdy,
                            const amrex::Real* dtsdz);

    void WRPX_PUSH_PML_EVEC_F(const int* xlo, const int* xhi,
                              const int* ylo, const int* yhi,
                              const int* zlo, const int* zhi,
                              BL_FORT_FAB_ARG_3D(ex),
                              BL_FORT_FAB_ARG_3D(ey),
                              BL_FORT_FAB_ARG_3D(ez),
                              const BL_FORT_FAB_ARG_3D(f),
                              const amrex::Real* dtsdx,
                              const amrex::Real* dtsdy,
                              const amrex::Real* dtsdz,
                              const int* maxwell_fdtd_solver_id);

    void WRPX_PUSH_PML_F(const int* lo, const int* hi,
                         BL_FORT_FAB_ARG_3D(f),
                         const BL_FORT_FAB_ARG_3D(ex),
                         const BL_FORT_FAB_ARG_3D(ey),
                         const BL_FORT_FAB_ARG_3D(ez),
                         const amrex::Real* dtsdx,
                         const amrex::Real* dtsdy,
                         const amrex::Real* dtsdz);

    void WRPX_DAMP_PML (const int* texlo, const int* texhi,
                        const int* teylo, const int* teyhi,
                        const int* tezlo, const int* tezhi,
                        const int* tbxlo, const int* tbxhi,
                        const int* tbylo, const int* tbyhi,
                        const int* tbzlo, const int* tbzhi,
                        amrex::Real* ex, const int* exlo, const int* exhi,
                        amrex::Real* ey, const int* eylo, const int* eyhi,
                        amrex::Real* ez, const int* ezlo, const int* ezhi,
                        amrex::Real* bx, const int* bxlo, const int* bxhi,
                        amrex::Real* by, const int* bylo, const int* byhi,
                        amrex::Real* bz, const int* bzlo, const int* bzhi,
                        const amrex::Real* sigex, int sigex_lo, int sigex_hi,
#if (AMREX_SPACEDIM == 3)
                        const amrex::Real* sigey, int sigey_lo, int sigey_hi,
#endif
                        const amrex::Real* sigez, int sigez_lo, int sigez_hi,
                        const amrex::Real* sigbx, int sigbx_lo, int sigbx_hi,
#if (AMREX_SPACEDIM == 3)
                        const amrex::Real* sigby, int sigby_lo, int sigby_hi,
#endif
                        const amrex::Real* sigbz, int sigbz_lo, int sigbz_hi);

    void WRPX_DAMP_PML_F (const int* tndlo, const int* tndhi,
                          amrex::Real* F,  const int* flo, const int* fhi,
                          const amrex::Real* sigex, int sigex_lo, int sigex_hi,
#if (AMREX_SPACEDIM == 3)
                          const amrex::Real* sigey, int sigey_lo, int sigey_hi,
#endif
                          const amrex::Real* sigez, int sigez_lo, int sigez_hi,
                          const amrex::Real* sigbx, int sigbx_lo, int sigbx_hi,
#if (AMREX_SPACEDIM == 3)
                          const amrex::Real* sigby, int sigby_lo, int sigby_hi,
#endif
                          const amrex::Real* sigbz, int sigbz_lo, int sigbz_hi);

    void WRPX_SYNC_CURRENT (const int* lo, const int* hi,
                             BL_FORT_FAB_ARG_ANYD(crse),
                             const BL_FORT_FAB_ARG_ANYD(fine),
                             const int* dir);

    void WRPX_SYNC_RHO (const int* lo, const int* hi,
                        BL_FORT_FAB_ARG_ANYD(crse),
                        const BL_FORT_FAB_ARG_ANYD(fine),
                        const int* ncomp);

#ifdef WARPX_USE_PSATD
    void warpx_fft_mpi_init (int fcomm);
    void warpx_fft_domain_decomp (int* warpx_local_nz, int* warpx_local_z0,
                                  const int* global_lo, const int* global_hi);
    void warpx_fft_dataplan_init (const int* nox, const int* noy, const int* noz,
                                  void* fft_data, const int* ndata,
                                  const amrex_real* dx_w, const amrex_real* dt_w,
                                  const int* fftw_plan_measure, const int* do_nodal );
    void warpx_fft_nullify ();
    void warpx_fft_push_eb (amrex_real* ex_w, const int* exlo, const int* exhi,
                            amrex_real* ey_w, const int* eylo, const int* eyhi,
                            amrex_real* ez_w, const int* ezlo, const int* ezhi,
                            amrex_real* bx_w, const int* bxlo, const int* bxhi,
                            amrex_real* by_w, const int* bylo, const int* byhi,
                            amrex_real* bz_w, const int* bzlo, const int* bzhi,
                            amrex_real* jx_w, const int* jxlo, const int* jxhi,
                            amrex_real* jy_w, const int* jylo, const int* jyhi,
                            amrex_real* jz_w, const int* jzlo, const int* jzhi,
                            amrex_real* rhoold_w, const int* r1lo, const int* r1hi,
                            amrex_real* rho_w, const int* r2lo, const int* r2hi);

#endif

    void warpx_build_buffer_masks (const int* lo, const int* hi,
                                   int* msk, const int* mlo, const int* mhi,
                                   const int* gmsk, const int* glo, const int* ghi, const int* ng);

#ifdef __cplusplus
}
#endif
