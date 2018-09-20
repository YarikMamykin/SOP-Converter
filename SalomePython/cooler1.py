import salome
import geompy
import smesh

def update_screen():
    if salome.sg.hasDesktop():
        salome.sg.updateObjBrowser(True)

## Geometry part ##
salome.salome_init()
geompy.init_geom(salome.myStudy)

cooler = geompy.MakeBoxDXDYDZ(30,20,70)
group = geompy.CreateGroup(cooler, geompy.ShapeType["FACE"])
geompy.addToStudy ( cooler, 'cooler' )

groups = []
counter = 0
for each_face in geompy.SubShapeAllSortedCentres(cooler, geompy.ShapeType["FACE"]): 
    groups.append (geompy.CreateGroup(cooler, geompy.ShapeType["FACE"]))
    geompy.AddObject (groups[counter], geompy.GetSubShapeID(cooler, each_face))
    geompy.addToStudyInFather (cooler, groups[counter], 'face_' + str(counter))
    counter+=1


update_screen()

## Mesh part ##
cooler_mesh = smesh.CreateMesh(cooler)
# execute dir(smesh.CreateMesh()) to have more info
update_screen()
