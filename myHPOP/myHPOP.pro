QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    calculate/ODE45.cpp \
    calculate/SOFA/a2af.c \
    calculate/SOFA/a2tf.c \
    calculate/SOFA/af2a.c \
    calculate/SOFA/anp.c \
    calculate/SOFA/anpm.c \
    calculate/SOFA/bi00.c \
    calculate/SOFA/bp00.c \
    calculate/SOFA/bp06.c \
    calculate/SOFA/bpn2xy.c \
    calculate/SOFA/c2i00a.c \
    calculate/SOFA/c2i00b.c \
    calculate/SOFA/c2i06a.c \
    calculate/SOFA/c2ibpn.c \
    calculate/SOFA/c2ixy.c \
    calculate/SOFA/c2ixys.c \
    calculate/SOFA/c2s.c \
    calculate/SOFA/c2t00a.c \
    calculate/SOFA/c2t00b.c \
    calculate/SOFA/c2t06a.c \
    calculate/SOFA/c2tcio.c \
    calculate/SOFA/c2teqx.c \
    calculate/SOFA/c2tpe.c \
    calculate/SOFA/c2txy.c \
    calculate/SOFA/cal2jd.c \
    calculate/SOFA/cp.c \
    calculate/SOFA/cpv.c \
    calculate/SOFA/cr.c \
    calculate/SOFA/d2dtf.c \
    calculate/SOFA/d2tf.c \
    calculate/SOFA/dat.c \
    calculate/SOFA/dtdb.c \
    calculate/SOFA/dtf2d.c \
    calculate/SOFA/ee00.c \
    calculate/SOFA/ee00a.c \
    calculate/SOFA/ee00b.c \
    calculate/SOFA/ee06a.c \
    calculate/SOFA/eect00.c \
    calculate/SOFA/eform.c \
    calculate/SOFA/eo06a.c \
    calculate/SOFA/eors.c \
    calculate/SOFA/epb.c \
    calculate/SOFA/epb2jd.c \
    calculate/SOFA/epj.c \
    calculate/SOFA/epj2jd.c \
    calculate/SOFA/epv00.c \
    calculate/SOFA/eqeq94.c \
    calculate/SOFA/era00.c \
    calculate/SOFA/fad03.c \
    calculate/SOFA/fae03.c \
    calculate/SOFA/faf03.c \
    calculate/SOFA/faju03.c \
    calculate/SOFA/fal03.c \
    calculate/SOFA/falp03.c \
    calculate/SOFA/fama03.c \
    calculate/SOFA/fame03.c \
    calculate/SOFA/fane03.c \
    calculate/SOFA/faom03.c \
    calculate/SOFA/fapa03.c \
    calculate/SOFA/fasa03.c \
    calculate/SOFA/faur03.c \
    calculate/SOFA/fave03.c \
    calculate/SOFA/fk52h.c \
    calculate/SOFA/fk5hip.c \
    calculate/SOFA/fk5hz.c \
    calculate/SOFA/fw2m.c \
    calculate/SOFA/fw2xy.c \
    calculate/SOFA/gc2gd.c \
    calculate/SOFA/gc2gde.c \
    calculate/SOFA/gd2gc.c \
    calculate/SOFA/gd2gce.c \
    calculate/SOFA/gmst00.c \
    calculate/SOFA/gmst06.c \
    calculate/SOFA/gmst82.c \
    calculate/SOFA/gst00a.c \
    calculate/SOFA/gst00b.c \
    calculate/SOFA/gst06.c \
    calculate/SOFA/gst06a.c \
    calculate/SOFA/gst94.c \
    calculate/SOFA/h2fk5.c \
    calculate/SOFA/hfk5z.c \
    calculate/SOFA/ir.c \
    calculate/SOFA/jd2cal.c \
    calculate/SOFA/jdcalf.c \
    calculate/SOFA/num00a.c \
    calculate/SOFA/num00b.c \
    calculate/SOFA/num06a.c \
    calculate/SOFA/numat.c \
    calculate/SOFA/nut00a.c \
    calculate/SOFA/nut00b.c \
    calculate/SOFA/nut06a.c \
    calculate/SOFA/nut80.c \
    calculate/SOFA/nutm80.c \
    calculate/SOFA/obl06.c \
    calculate/SOFA/obl80.c \
    calculate/SOFA/p06e.c \
    calculate/SOFA/p2pv.c \
    calculate/SOFA/p2s.c \
    calculate/SOFA/pap.c \
    calculate/SOFA/pas.c \
    calculate/SOFA/pb06.c \
    calculate/SOFA/pdp.c \
    calculate/SOFA/pfw06.c \
    calculate/SOFA/plan94.c \
    calculate/SOFA/pm.c \
    calculate/SOFA/pmat00.c \
    calculate/SOFA/pmat06.c \
    calculate/SOFA/pmat76.c \
    calculate/SOFA/pmp.c \
    calculate/SOFA/pn.c \
    calculate/SOFA/pn00.c \
    calculate/SOFA/pn00a.c \
    calculate/SOFA/pn00b.c \
    calculate/SOFA/pn06.c \
    calculate/SOFA/pn06a.c \
    calculate/SOFA/pnm00a.c \
    calculate/SOFA/pnm00b.c \
    calculate/SOFA/pnm06a.c \
    calculate/SOFA/pnm80.c \
    calculate/SOFA/pom00.c \
    calculate/SOFA/ppp.c \
    calculate/SOFA/ppsp.c \
    calculate/SOFA/pr00.c \
    calculate/SOFA/prec76.c \
    calculate/SOFA/pv2p.c \
    calculate/SOFA/pv2s.c \
    calculate/SOFA/pvdpv.c \
    calculate/SOFA/pvm.c \
    calculate/SOFA/pvmpv.c \
    calculate/SOFA/pvppv.c \
    calculate/SOFA/pvstar.c \
    calculate/SOFA/pvu.c \
    calculate/SOFA/pvup.c \
    calculate/SOFA/pvxpv.c \
    calculate/SOFA/pxp.c \
    calculate/SOFA/rm2v.c \
    calculate/SOFA/rv2m.c \
    calculate/SOFA/rx.c \
    calculate/SOFA/rxp.c \
    calculate/SOFA/rxpv.c \
    calculate/SOFA/rxr.c \
    calculate/SOFA/ry.c \
    calculate/SOFA/rz.c \
    calculate/SOFA/s00.c \
    calculate/SOFA/s00a.c \
    calculate/SOFA/s00b.c \
    calculate/SOFA/s06.c \
    calculate/SOFA/s06a.c \
    calculate/SOFA/s2c.c \
    calculate/SOFA/s2p.c \
    calculate/SOFA/s2pv.c \
    calculate/SOFA/s2xpv.c \
    calculate/SOFA/sepp.c \
    calculate/SOFA/seps.c \
    calculate/SOFA/sp00.c \
    calculate/SOFA/starpm.c \
    calculate/SOFA/starpv.c \
    calculate/SOFA/sxp.c \
    calculate/SOFA/sxpv.c \
    calculate/SOFA/t_sofa_c.c \
    calculate/SOFA/taitt.c \
    calculate/SOFA/taiut1.c \
    calculate/SOFA/taiutc.c \
    calculate/SOFA/tcbtdb.c \
    calculate/SOFA/tcgtt.c \
    calculate/SOFA/tdbtcb.c \
    calculate/SOFA/tdbtt.c \
    calculate/SOFA/tf2a.c \
    calculate/SOFA/tf2d.c \
    calculate/SOFA/tr.c \
    calculate/SOFA/trxp.c \
    calculate/SOFA/trxpv.c \
    calculate/SOFA/tttai.c \
    calculate/SOFA/tttcg.c \
    calculate/SOFA/tttdb.c \
    calculate/SOFA/ttut1.c \
    calculate/SOFA/ut1tai.c \
    calculate/SOFA/ut1tt.c \
    calculate/SOFA/ut1utc.c \
    calculate/SOFA/utctai.c \
    calculate/SOFA/utcut1.c \
    calculate/SOFA/xy06.c \
    calculate/SOFA/xys00a.c \
    calculate/SOFA/xys00b.c \
    calculate/SOFA/xys06a.c \
    calculate/SOFA/zp.c \
    calculate/SOFA/zpv.c \
    calculate/SOFA/zr.c \
    calculate/TB.cpp \
    calculate/a.cpp \
    calculate/jpl/jpleph.cpp \
    calculate/nrlmsise00/nrlmsise-00.c \
    calculate/nrlmsise00/nrlmsise-00_data.c \
    calculate/timecoor.cpp \
    daytimedrawarea.cpp \
    earth2d.cpp \
    earth3d.cpp \
    inputperturbationwidget.cpp \
    inputsatellitestartposwidget.cpp \
    inputscenariowidget.cpp \
    main.cpp \
    mainwindow.cpp \
    outputorbittextwidget.cpp \
    satellite.cpp \
    scenario.cpp \
    timewidget.cpp \
    wholetimedrawarea.cpp

HEADERS += \
    calculate/ODE45.h \
    calculate/SOFA/sofa.h \
    calculate/SOFA/sofam.h \
    calculate/TB.h \
    calculate/a.h \
    calculate/jpl/jpl_int.h \
    calculate/jpl/jpleph.h \
    calculate/nrlmsise00/nrlmsise-00.h \
    calculate/timecoor.h \
    daytimedrawarea.h \
    earth2d.h \
    earth3d.h \
    inputperturbationwidget.h \
    inputsatellitestartposwidget.h \
    inputscenariowidget.h \
    mainwindow.h \
    outputorbittextwidget.h \
    satellite.h \
    scenario.h \
    timewidget.h \
    wholetimedrawarea.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    calculate/jpl/de405.bin
