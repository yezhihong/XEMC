# XEMC: Quasielastic Cross Section Model
##  Developed and maintained by Zhihong Ye.
##  630-252-2305, yez@jlab.org

In this code, both the unradiated (Born) Cross Section and the Radiated Cross Section are given.
The DIS part of the Born Cross Section is based on the F2ALLM model, and
the QE part is based on the F(y) scalling function with the parameters fitted from the
Hall-C E02-019 data and Hall-A E08-014 data. These two models are default in the code,
and a DIS model which was twisted for EMC study from Peter's F1F2IN06 fit is also given in the code and it is completely in C++.
The QFS model is also embeded inside for other purposes.

For the Radiated Cross Section, the Peaking Approximation method is used to evaluated
the radiation effect. The method has been compared with a more advanced radiation
correction method with full integrals, and in the QE region, the Peaking-Approximation
give 3% less radiation effect. Keep in mind that the Coulomb Effect is considered when
calculating Radiated Cross Section.

All parameters related to the target system, the spectrometer windows are given in the
./input/ where each target is given by a separated file. The list of targets which this
code can calculate is given in ./SRC/target.table. You can add the input parameter
file if you want to add a new target included in the list.

An example, Check_XS.C, is included in this file so you can understand how to make use
of this code. Please feel free to ask me if you have any questions.
