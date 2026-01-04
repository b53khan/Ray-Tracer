-- test for hierarchical ray-tracers.
-- Thomas Pflaum 1996

gold = gr.material({0.9, 0.8, 0.4}, {0.8, 0.8, 0.4}, 25)
grass = gr.material({0.1, 0.7, 0.1}, {0.0, 0.0, 0.0}, 0)
blue = gr.material({0.7, 0.6, 1}, {0.5, 0.4, 0.8}, 25)
water = gr.material({0.05, 0.05, 0.05}, {0.0, 0.7, 0.7}, 25, true)
mat3 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25)
mat4 = gr.material({0.7, 0.6, 1.0}, {0.5, 0.4, 0.8}, 25)

scene = gr.node('scene')
scene:rotate('X', 23)
scene:translate(200, 0, -800)

-- the floor
plane = gr.mesh( 'plane', 'plane.obj' )
scene:add_child(plane)
plane:set_material(water)
plane:scale(800, 800, 800)
plane:translate(-200, -100, 0);

-- Textured ball
s2 = gr.nh_sphere('s2', {-100, 50, 100}, 150)
scene:add_child(s2)
s2:set_material(mat3)
s2:set_texture("b2.png")
s2:rotate('X', 8)

b1 = gr.nh_box('b1', {-400, -100, -500}, 150)
scene:add_child(b1)
b1:set_material(mat4)
b1:rotate('Y', 25)

-- The lights
l1 = gr.light({200,200,400}, {0.8, 0.8, 0.8}, {1, 0, 0})
l2 = gr.light({0, 5, -20}, {0.4, 0.4, 0.8}, {1, 0, 0})

l3 = gr.light({200,200,400}, {0.5, 0.5, 0.5}, {1, 0, 0}) 	-- Reduced intensity
l4 = gr.light({0, 5, -20}, {0.2, 0.2, 0.4}, {1, 0, 0}) 		-- Reduced intensity

gr.render(scene, 'final2.png', 256, 256, 
	  {0, 0, 0,}, {0, 0, -1}, {0, 1, 0}, 50,
	  {0.4, 0.4, 0.4}, {l3})
