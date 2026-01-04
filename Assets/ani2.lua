local folderPath = "frames/"

gold = gr.material({0.9, 0.8, 0.4}, {0.8, 0.8, 0.4}, 25)
grass = gr.material({0.1, 0.7, 0.1}, {0.0, 0.0, 0.0}, 0)
blue = gr.material({0.7, 0.6, 1}, {0.5, 0.4, 0.8}, 25)
water = gr.material( {0.05, 0.05, 0.05}, {0.7, 0.7, 0.7}, 25, 1.3333)
mat3 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25)

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
s2 = gr.nh_sphere('s2', {0, 0, 0}, 100)
scene:add_child(s2)
s2:set_texture("b2.png")
s2:set_material(mat3)

-- The lights
l1 = gr.light({200,200,400}, {0.8, 0.8, 0.8}, {1, 0, 0})
l2 = gr.light({0, 5, -20}, {0.4, 0.4, 0.8}, {1, 0, 0})

l3 = gr.light({200,200,400}, {0.5, 0.5, 0.5}, {1, 0, 0})  	-- Reduced intensity
l4 = gr.light({0, 5, -20}, {0.2, 0.2, 0.4}, {1, 0, 0}) 		-- Reduced intensity

-- Animation parameters
local totalTime = 1 				-- Total animation time in seconds
local fps = 24 						-- Frames per second
local numFrames = totalTime * fps 	-- Total number of frames
local bounceDuration = 1 			-- Duration of each bounce in seconds
local bounceHeight = 10   			-- Height of the bounce

local width = 256
local height = 256
local fov = 50
local cameraPosition = {0, 0, 0}
local cameraDirection = {0, 0, -1}
local upVector = {0, 1, 0}

-- Animation loop
for i = 1, numFrames do
    -- Calculate time within the bounce duration
    local t = (i - 1) % (bounceDuration * fps) / fps

    -- Calculate vertical position of the ball
    local y = math.sin(math.pi * t / bounceDuration) * bounceHeight

    -- Update ball position
    s2:translate(0, y, 0)

    local filename = string.format("%sframe_%03d.png", folderPath, i)

    -- Render the scene
    gr.render(scene, filename, width, height,
        cameraPosition, cameraDirection, upVector, fov, {0.4, 0.4, 0.4}, {l3})

end
