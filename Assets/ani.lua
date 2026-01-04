-- Final project scene with a textured ball and a cube
-- The ball bounces and the cube moves in an arc 
-- The plane surface is reflective and reflects the ball and cube

-- The materials
water = gr.material({0.05, 0.05, 0.05}, {0.0, 0.7, 0.7}, 25, true)
mat1 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25)
mat2 = gr.material({0.7, 0.6, 1.0}, {0.5, 0.4, 0.8}, 25)

-- The scene
scene = gr.node('scene')
scene:rotate('X', 23)
scene:translate(200, 0, -800)

-- The floor
plane = gr.mesh('plane', 'plane.obj')
scene:add_child(plane)
plane:set_material(water)
plane:scale(800, 800, 800)
plane:translate(-200, -100, 0)

-- The textured ball
s2 = gr.nh_sphere('s2', {-100, 50, 120}, 150)
scene:add_child(s2)
s2:set_material(mat1)
s2:set_texture("b2.png")     --source: https://www.pexels.com/photo/orange-leather-207300/

s2:rotate('X', 8)

local frame_start = 7

-- The cube
b1 = gr.nh_box('b1', {-375, -100, -500}, 150)
scene:add_child(b1)
b1:set_material(mat2)
b1:rotate('Y', 20)
b1:rotate('X', (frame_start-1)*0.35)

-- The lights
l = gr.light({300,50,400}, {0.5, 0.5, 0.5}, {1, 0, 0})


local bounce_height = 5
local period = 15

function animate(frame)
    print(frame)
    local num = frame % (2 * period)
    if num <= period and num > 0 then
        s2:translate(0, bounce_height, 0)
    else
        s2:translate(0, -bounce_height, 0)
    end
    b1:rotate('X', 0.35)
    return scene
end

-- Render the animation
frame_count = 420 -- 10 seconds * 24 frames per second
for frame = frame_start, frame_count do
    local animated_scene = animate(frame)
    local filename = string.format("frames/frame_%03d.png", frame)
    gr.render(animated_scene, filename, 456, 456, 
              {0, 0, 0}, {0, 0, -1}, {0, 1, 0}, 50,
              {0.4, 0.4, 0.4}, {l})
end
