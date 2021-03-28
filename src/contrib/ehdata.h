/*
 * This file is part of the GROMACS molecular simulation package.
 *
 * Copyright (c) 1991-2000, University of Groningen, The Netherlands.
 * Copyright (c) 2001-2004, The GROMACS development team,
 * check out http://www.gromacs.org for more information.
 * Copyright (c) 2012,2013, by the GROMACS development team, led by
 * David van der Spoel, Berk Hess, Erik Lindahl, and including many
 * others, as listed in the AUTHORS file in the top-level source
 * directory and at http://www.gromacs.org.
 *
 * GROMACS is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * GROMACS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with GROMACS; if not, see
 * http://www.gnu.org/licenses, or write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.
 *
 * If you want to redistribute modifications to GROMACS, please
 * consider that scientific software is very special. Version
 * control is crucial - bugs must be traceable. We will be happy to
 * consider code for inclusion in the official distribution, but
 * derived work must not be called official GROMACS. Details are found
 * in the README & COPYING files - if they are missing, get the
 * official version at http://www.gromacs.org.
 *
 * To help us fund GROMACS development, we humbly ask that you cite
 * the research papers on the package. Check out http://www.gromacs.org.
 */
	
extern real get_omega(real ekin,int *seed,FILE *fp,char *fn);

extern real get_q_inel(real ekin,real omega,int *seed,FILE *fp,char *fn);

extern real get_theta_el(real ekin,int *seed,FILE *fp,char *fn);

extern real cross_inel(real ekin,real rho,char *fn);

extern real cross_el(real ekin,real rho,char *fn);

extern real band_ener(int *seed,FILE *fp,char *fn);

extern void init_tables(int nfile,t_filenm fnm[], real rho);
/* Must be called before any of the table lookup thingies */

extern void test_tables(int *seed,char *fn,real rho);

/*******************************************************************
 *
 * Functions to make histograms
 *
 *******************************************************************/	
	
enum { enormNO, enormFAC, enormNP, enormNR };

typedef struct {
  int np;
  real minx,maxx,dx,dx_1;
  real *y;
  int  *nh;
} t_histo;

extern t_histo *init_histo(int np,real minx,real maxx);

extern void done_histo(t_histo *h);

extern void add_histo(t_histo *h,real x,real y);

extern void dump_histo(t_histo *h,char *fn,char *title,char *xaxis,char *yaxis,
		       int enorm,real norm_fac);


/*******************************************************************
 *
 * Functions to analyse and monitor scattering
 *
 *******************************************************************/	
	
typedef struct {
  int  np,maxp;
  real *time;
  real *ekin;
  gmx_bool *bInel;
  rvec *pos;
} t_ana_scat;

extern void add_scatter_event(t_ana_scat *scatter,rvec pos,gmx_bool bInel,
			      real t,real ekin);
			      
extern void reset_ana_scat(t_ana_scat *scatter);

extern void done_scatter(t_ana_scat *scatter);

extern void analyse_scatter(t_ana_scat *scatter,t_histo *hmfp);

/*******************************************************************
 *
 * Functions to analyse structural changes
 *
 *******************************************************************/	

typedef struct {
  int  nanal,index;
  real dt;
  real *t;
  real *maxdist;
  rvec *d2_com,*d2_origin;
  int  *nion;
  int  nstruct,nparticle,maxparticle;
  rvec *q;
  rvec **x;
} t_ana_struct;

extern t_ana_struct *init_ana_struct(int nstep,int nsave,real timestep,
				     int maxparticle);

extern void done_ana_struct(t_ana_struct *anal);

extern void reset_ana_struct(t_ana_struct *anal);

extern void add_ana_struct(t_ana_struct *total,t_ana_struct *add);

extern void analyse_structure(t_ana_struct *anal,real t,rvec center,
			      rvec x[],int nparticle,real charge[]);

extern void dump_ana_struct(char *rmax,char *nion,char *gyr_com,
			    char *gyr_origin,t_ana_struct *anal,int nsim);

extern void dump_as_pdb(char *pdb,t_ana_struct *anal);

/*******************************************************************
 *
 * Functions to analyse energies
 *
 *******************************************************************/	
			    
enum { eCOUL, eREPULS, ePOT, eHOLE, eELECTRON, eLATTICE, eKIN, eTOT, eNR };
extern char *enms[eNR];

typedef real evec[eNR];

typedef struct {
  int  nx,maxx;
  evec *e;
} t_ana_ener;

extern void add_ana_ener(t_ana_ener *ae,int nn,real e[]);

extern void dump_ana_ener(t_ana_ener *ae,int nsim,real dt,char *edump,
			  t_ana_struct *total);
