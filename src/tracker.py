# src/tracker.py

from datetime import datetime




class FitnessTracker:

    def __init__(self):
        self.workouts = []


    def new_workout(self, workout_name, calories, duration):

        """ 
        Function adds new workout to the fitness tracker
        
        :param activity_name: Type of activity e.g Cycling, Pushups.
        :param calories: amount of calories burned uring activity
        :param duration: Times spent during the activity in minutes
        
        """

        workout = {
            'workout_id': len(self.workouts) + 1,
            'Type': workout_name,
            'calories': calories,
            'duration': duration,
            'date': datetime.now().strftime("%Y-%m-%d")

        }

        self.workouts.append(workout)
        return workout
    
     