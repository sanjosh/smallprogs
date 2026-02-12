
import numpy as np

# -----------------------------
# PID Controller
# -----------------------------
class PIDController:
    def __init__(self, Kp, Ki, Kd, dt):
        self.Kp = Kp
        self.Ki = Ki
        self.Kd = Kd
        self.dt = dt
        self.integral = 0.0
        self.prev_error = 0.0

    def compute(self, error):
        # Integral term
        self.integral += error * self.dt

        # Derivative term
        derivative = (error - self.prev_error) / self.dt

        # PID output (negative feedback)
        output = -(self.Kp * error +
                   self.Ki * self.integral +
                   self.Kd * derivative)

        self.prev_error = error
        return output


# -----------------------------
# Simulation
# -----------------------------
lane_offset = 0.5     # meters from center
speed = 20.0          # m/s (~72 km/h)
road_curvature = 0.02

dt = 0.2
steps = 40

# Limits
max_accel = 2.0
max_brake = -3.0
max_speed = 30.0
lane_half_width = 1.75

# PID gains (tuned roughly)
pid = PIDController(Kp=4.0, Ki=0.5, Kd=1.5, dt=dt)

print("time  offset(m)  speed(m/s)  pedal(m/s^2)")
print("-------------------------------------------")

for t in range(steps):

    # PID uses current lane error only
    error = lane_offset
    pedal = pid.compute(error)

    # Apply actuator limits
    pedal = np.clip(pedal, max_brake, max_accel)

    # Update vehicle dynamics
    speed = np.clip(speed + dt * pedal, 0.0, max_speed)
    lane_offset = lane_offset + dt * speed * road_curvature

    # Check lane boundary
    if abs(lane_offset) > lane_half_width:
        print("Car left the lane!")
        break

    print(f"{t*dt:4.1f}    {lane_offset:6.3f}      {speed:6.2f}        {pedal:5.2f}")
