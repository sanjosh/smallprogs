
import numpy as np

# -----------------------------
# MPC solver
# -----------------------------
def decide_throttle_or_brake(
    lane_offset,
    speed,
    road_curvature,
    last_pedal
):
    # MPC parameters
    horizon_steps = 8
    dt = 0.2

    # Limits
    max_accel = 2.0
    max_brake = -3.0
    max_speed = 30.0
    lane_half_width = 1.75

    # Cost weights
    lane_weight = 1.0
    smoothness_weight = 0.3

    # Candidate pedal values (brute force)
    pedal_candidates = [-3.0, -1.5, 0.0, 1.0, 2.0]

    best_cost = float("inf")
    best_plan = None

    # Try all pedal sequences (very small horizon!)
    def search(plan, depth):
        nonlocal best_cost, best_plan

        if depth == horizon_steps:
            # Evaluate this plan
            x = lane_offset
            v = speed
            prev_pedal = last_pedal
            cost = 0.0

            for u in plan:
                # Predict dynamics
                v = np.clip(v + dt * u, 0.0, max_speed)
                x = x + dt * v * road_curvature

                # Cost terms
                cost += lane_weight * (x ** 2)
                cost += smoothness_weight * ((u - prev_pedal) ** 2)

                # Constraints
                if abs(x) > lane_half_width:
                    cost += 1e6  # huge penalty

                prev_pedal = u

            if cost < best_cost:
                best_cost = cost
                best_plan = plan.copy()

            return

        for u in pedal_candidates:
            search(plan + [u], depth + 1)

    search([], 0)

    return best_plan


# -----------------------------
# Simulation loop
# -----------------------------
lane_offset = 0.5     # meters from center
speed = 20.0          # m/s (~72 km/h)
road_curvature = 0.02 # constant curve
last_pedal = 0.0

dt = 0.2
steps = 40

print("time  offset(m)  speed(m/s)  pedal(m/s^2)")
print("-------------------------------------------")

for t in range(steps):
    pedal_plan = decide_throttle_or_brake(
        lane_offset,
        speed,
        road_curvature,
        last_pedal
    )

    pedal = pedal_plan[0]

    # Apply control
    speed = np.clip(speed + dt * pedal, 0.0, 30.0)
    lane_offset = lane_offset + dt * speed * road_curvature

    print(f"{t*dt:4.1f}    {lane_offset:6.3f}      {speed:6.2f}        {pedal:5.2f}")

    last_pedal = pedal
