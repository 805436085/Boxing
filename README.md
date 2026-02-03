# Boxing

## Behavior Tree Service - Enemy Detection

The project includes a custom Behavior Tree Service (`BTService_DetectEnemy`) for periodic enemy detection.

### Features

- **Periodic Detection**: Automatically scans for enemies at configurable intervals (default: 0.5 seconds). The `Interval` and `RandomDeviation` properties are inherited from the base `BTService` class and can be adjusted in the Behavior Tree editor.
- **Range-Based Detection**: Detects enemies within a specified range (default: 1000 units)
- **Tag-Based Filtering**: Identifies enemies using Actor tags (default: "Enemy")
- **Blackboard Integration**: Stores the closest detected enemy in the Behavior Tree Blackboard
- **Debug Visualization**: Shows detection range in the editor with color-coded spheres (red when enemy detected, green otherwise)
- **Performance Optimized**: Uses physics sphere overlap queries for efficient detection

### Usage

1. **In Behavior Tree Editor**:
   - Add the "Detect Enemy" service to any Composite node in your Behavior Tree
   - Configure the service properties:
     - `Detection Range`: Set the maximum distance to detect enemies
     - `Enemy Actor Key`: Select the Blackboard key to store the detected enemy (must be of type Object)
     - `Enemy Tag`: Set the tag used to identify enemy actors

2. **In Your AI Controller**:
   - Ensure your AI Controller has a Blackboard and Behavior Tree component
   - Create a Blackboard asset with an Object key for storing the enemy reference

3. **Tag Your Enemies**:
   - Add the "Enemy" tag (or your custom tag) to enemy character actors in the level or character blueprint

### Example Configuration

```
Detection Range: 1000.0
Enemy Actor Key: TargetEnemy (Object type in Blackboard)
Enemy Tag: Enemy
```

The service will automatically find the closest enemy within range and update the Blackboard key, allowing other Behavior Tree tasks to react to detected enemies.

