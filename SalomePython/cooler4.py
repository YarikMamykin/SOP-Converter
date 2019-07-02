import salome
import geompy
import smesh, SMESH

def split_cooler_to_faces(cooler_obj):
    groups = []
    counter = 0
    for each_face in geompy.SubShapeAllSortedCentres(cooler, geompy.ShapeType["FACE"]): 
        groups.append (geompy.CreateGroup(cooler, geompy.ShapeType["FACE"]))
        geompy.AddObject (groups[counter], geompy.GetSubShapeID(cooler, each_face))
        geompy.addToStudyInFather (cooler, groups[counter], 'face_' + str(counter+1))
        counter+=1
    return groups

def update_screen():
    if salome.sg.hasDesktop():
        salome.sg.updateObjBrowser(True)

## Geometry part ##
salome.salome_init()
geompy.init_geom(salome.myStudy)

cyl_rad = 10
cyl_height = 40
box_final_coords = [ 100, 30, 100 ]
points_offset = 35
vectorOY = geompy.MakeVector(geompy.MakeVertex(0,0,0), geompy.MakeVertex(0,100,0))

box = geompy.MakeBoxDXDYDZ(box_final_coords[0], box_final_coords[1],box_final_coords[2])
box = geompy.MakeRotation(box, vectorOY, 45)
geompy.addToStudy ( box, 'box' )

diagons = [ geompy.MakeLineTwoPnt(geompy.MakeVertex( 0,box_final_coords[1], 0 ), geompy.MakeVertex( box_final_coords[0],box_final_coords[1], box_final_coords[2])), geompy.MakeLineTwoPnt(geompy.MakeVertex( box_final_coords[0], box_final_coords[1], 0 ), geompy.MakeVertex( 0, box_final_coords[1], box_final_coords[2]))]
for counter in range(1,3):
    diagons[counter-1] = geompy.MakeRotation(diagons[counter-1], vectorOY, 45)
    geompy.addToStudy( diagons[counter-1], 'diagon_' + str(counter) )

central_point = geompy.MakeVertexOnLinesIntersection(diagons[0], diagons[1])

points = [ geompy.MakeVertexWithRef(central_point, -points_offset, 0, 0), geompy.MakeVertexWithRef(central_point, points_offset, 0, 0) ]
for each_point,counter in zip(points, range(1,3)):
    geompy.addToStudy ( each_point, 'point_' + str(counter) )

cyls = []
for each_point,counter in zip(points, range(0,2)):
    cyls.append( geompy.MakeCylinder(each_point, vectorOY, cyl_rad, cyl_height) )
    geompy.addToStudy ( cyls[counter], 'Cylinder_' + str(counter + 1) )

cooler = geompy.MakeFuse(geompy.MakeFuse(box, cyls[0]), cyls[1])
geompy.addToStudy(cooler, 'cooler')

geom_faces = split_cooler_to_faces(cooler)[:]

update_screen()

## Mesh part ##
smesh.SetCurrentStudy(salome.myStudy)
cooler_mesh = smesh.CreateMesh(cooler)
update_screen()
for geom_face in geom_faces:
    mesh_group = cooler_mesh.CreateGroupFromGEOM(SMESH.FACE,geom_face.GetName(),geom_face)
update_screen()


