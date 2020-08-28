# Tauola


Notes for myself: 

ela.tgz goes to TAUOLA/TAUOLA/TauSpinner/src
incl.tgz to TAUOLA/TAUOLA/TauSpinner/include/TauSpinner

tauola_extras.f (this is mainly redefine the alpha_qed for Z scale)  to TAUOLA/TAUOLA/src/tauolaFortranInterfaces
tau-reweight-test.cxx  to /TAUOLA/TAUOLA/TauSpinner/examples


Setup and compile KKMC
  425  tar -xvf KK-all-chrpv.tgz
  426  cd KK-all/
  427  make Clean
  429  cd ffbench
  430  make Clean
  431  make makflag
  433  emacs -nw ../tauola/makefile   # fix the F&& flag to gfortran
  434  make
  437  cd ../dizet-6.45
  438  make table.all



Makefile_TAUOLA_EXAMPLES  and taumain_pythia_example.c  goes to external/TAUOLA/TAUOLA/examples to produce the HEPMC format output