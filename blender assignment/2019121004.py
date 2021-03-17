import bpy
from random import randrange
import random
import sys, os

bpy.ops.object.select_all(action='SELECT')
bpy.ops.object.delete(use_global=False, confirm=False)


tex = bpy.data.textures.new("tex.png", 'IMAGE')


wall = (0.1, 1, 6)
bpy.ops.mesh.primitive_cube_add(enter_editmode=False, calc_uvs=True, align='WORLD', location=(-5, 0, 3), scale=wall)
bpy.ops.mesh.primitive_cube_add(enter_editmode=False, calc_uvs=True, align='WORLD', location=(5, 0, 3), scale=wall)

cube = (0.7,0.7,0.7)
bpy.ops.mesh.primitive_cube_add(enter_editmode=False, calc_uvs=True, align='WORLD', location=(1.5, 0, 5.5), scale=cube)
bpy.ops.mesh.primitive_cube_add(enter_editmode=False, calc_uvs=True, align='WORLD', location=(-1.5, 0, 5.5), scale=cube)

bpy.ops.mesh.primitive_cube_add(enter_editmode=False, calc_uvs=True, align='WORLD', location=(1.5, 0, 2.5), scale=cube)
bpy.ops.mesh.primitive_cube_add(enter_editmode=False, calc_uvs=True, align='WORLD', location=(-1.5, 0, 2.5), scale=cube)

rack = (10, 1, 0.1)
bpy.ops.mesh.primitive_cube_add(enter_editmode=False, calc_uvs=True, align='WORLD', location=(0, 0, 5), scale=rack)
bpy.ops.mesh.primitive_cube_add(enter_editmode=False, calc_uvs=True, align='WORLD', location=(0, 0, 2), scale=rack)

