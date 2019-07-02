import salome
#import GEOM
import geompy
#from salome.geom import geomBuilder

salome.salome_init()
geompy.init_geom(salome.myStudy)

box_1 = geompy.MakeBoxDXDYDZ(10,30,40)
geompy.addToStudy ( box_1, 'My lovely box' )

cyl_1 = geompy.MakeCylinderRH ( 10, 30 )
geompy.addToStudy ( cyl_1, 'my lovely cylinder' )

if salome.sg.hasDesktop():
	salome.sg.updateObjBrowser(True)

