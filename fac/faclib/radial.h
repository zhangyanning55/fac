#ifndef _RADIAL_H_
#define _RADIAL_H_

#include <time.h>
#include <math.h>

#include "global.h"
#include "nucleus.h"
#include "interpolation.h"
#include "grid.h"
#include "coulomb.h"
#include "orbital.h"
#include "config.h"
#include "angular.h"
#include "recouple.h"

#define G_COULOMB   1
#define G_BABUSHKIN 2
#define M_FR        0
#define M_NR        1

#define ORBITALS_BLOCK    1000 /* # of orbitals in one block*/

#ifdef PERFORM_STATISTICS
typedef struct _RAD_TIMING_ {
  clock_t radial_1e;
  clock_t radial_2e;
  clock_t dirac;
  clock_t radial_slater;
} RAD_TIMING;

int GetRadTiming(RAD_TIMING *t);
#endif

int SetAWGrid(int n, double min, double max);
int SetRadialGrid(double rmin, double rmax);
int SetPotential(AVERAGE_CONFIG *acfg);
int GetPotential(char *s);
double GetResidualZ();
double GetRMax();

/* solve the dirac equation for the given orbital */
int SolveDirac(ORBITAL *orb);

/* get the index of the given orbital in the table */
int OrbitalIndex(int n, int kappa, double energy);
int OrbitalExists(int n, int kappa, double energy);
int AddOrbital(ORBITAL *orb);
ORBITAL *GetOrbital(int k);
ORBITAL *GetNewOrbital();
int GetNumBounds();
int GetNumOrbitals();
int GetNumContinua();

double GetPhaseShift(int k);

/* radial optimization */
int SetAverageConfig(int nshells, int *n, int *kappa, double *nq);
void SetOptimizeControll(double tolerence, int maxiter, int iprint);
void SetScreening(int n_screen, int *screened_n, 
		  double screened_harge, int kl);
int OptimizeRadial(int ng, int *kg, double *weight);
double TotalEnergyGroup(int kg);
double AverageEnergyConfig(CONFIG *cfg);

/* routines for radial integral calculations */
int GetYk(int k, double *yk, ORBITAL *orb1, ORBITAL *orb2, int type);
int Integrate(double *f, ORBITAL *orb1, ORBITAL *orb2, int type, double *r);
int IntegrateSubRegion(int i0, int i1, 
		       double *f, ORBITAL *orb1, ORBITAL *orb2,
		       int t, double *r, int m);
int IntegrateSinCos(int j, double *x, double *y, 
		    double *phase, double *dphase, 
		    int i0, double *r, int t);
int SlaterTotal(double *sd, double *se, int *js, int *ks, int k, int mode);
int Slater(double *s, int k0, int k1, int k2, int k3, int k, int mode);
void SortSlaterKey(int *kd);
int ResidualPotential(double *s, int k0, int k1);
int FreeResidualArray();
int FreeMultipoleArray();
int FreeSlaterArray();
int FreeMomentsArray();

double RadialMoments(int m, int k1, int k2);
double MultipoleRadialNR(int m, int k1, int k2, int guage);
double MultipoleRadialFR(double aw, int m, int k1, int k2, int guage);
double InterpolateMultipole(double aw2, int n, double *x, double *y);

int SaveOrbital(int i);
int RestoreOrbital(int i); 
int FreeOrbital(int i);
int SaveAllContinua(int mode); 
int SaveContinua(double e, int mode);
int FreeAllContinua();
int FreeContinua(double e);

int InitRadial();

#endif
