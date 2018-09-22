import salome
import geompy
import smesh, SMESH

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
smesh.SetCurrentStudy(salome.myStudy)
cooler_mesh = smesh.CreateMesh(cooler)
#update_screen()
for geom_group in groups:
    mesh_group = cooler_mesh.CreateGroupFromGEOM(SMESH.FACE,geom_group.GetName(),geom_group)
update_screen()


#algo = smesh.Mesh_Algorithm()

#Create(self, mesh, geom, hypo, so='libStdMeshersEngine.so') unbound smesh_algorithm.Mesh_Algorithm method
# execute dir(smesh.CreateMesh()) to have more info



#help (smesh.Mesh_Algorithm.Assign)
#Help on method Assign in module smesh_algorithm:

#Assign(self, algo, mesh, geom) unbound smesh_algorithm.Mesh_Algorithm method

