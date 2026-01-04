import os

# Path to the folder containing the frames
frames_folder = 'frames/'

# Output video filename
output_video = 'animation.mp4'

# Run ffmpeg command to concatenate frames into a video
os.system('ffmpeg -framerate 24 -i ' + frames_folder + 'frame_%03d.png -c:v libx264 -pix_fmt yuv420p ' + output_video)
