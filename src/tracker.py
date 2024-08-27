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
    

    def get_workouts(self, date=None):

         """ 
        Get's all workouts that occured on a date.
        
        :param date: Date is input/defined in the "YYYY-MM-DD" format, and returns all workouts
         that occurs on that date. If date is input as none the workouts are returned for the current date
        :return: activities is listed for the specfic date.
        """
         
         if date is None:
             date = datetime.now().strftime("%Y-%m-%d")
         return [workout for workout in self.workouts if workout['date'] == date]
    

    def get_summary_date(self, date=None):

         """ 
         Count's up all time spent and calories burned on activities for a specific date
        
         :param date: Date is input/defined in the "YYYY-MM-DD" format, and returns all workouts
         that occurs on that date. If date is input as none the total duration and calories burned are
         returned for the current date

        :return: Outputs the total duration and total calories burned
        """
           
         workouts = self.get_workouts(date)
        
         total_time = sum(workout['duration'] for workout in workouts)
         total_caloriesBurned = sum(workout['calories'] for workout in workouts)

         return {
            'date': date or datetime.now().strftime("%Y-%m-%d"),
            'total_duration': total_time,
            'total_calories': total_caloriesBurned
        }
          
             
        

         
    
    
     