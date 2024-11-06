class UserHashTable:
    def __init__(self):
        """Initialize the hash table."""
        self.user_table = {}  # This will hold the username as key and profile data as value

    def add_user(self, username: str, profile_data: dict):
        """Add a user profile to the hash table.

        Args:
            username (str): The unique username of the user.
            profile_data (dict): A dictionary containing user profile information.
        """
        if username in self.user_table:
            raise ValueError(f"Username '{username}' already exists.")
        self.user_table[username] = profile_data

    def get_user(self, username: str) -> dict:
        """Retrieve the user profile associated with the given username.

        Args:
            username (str): The unique username of the user.

        Returns:
            dict: The profile data of the user.

        Raises:
            KeyError: If the username does not exist in the hash table.
        """
        if username not in self.user_table:
            raise KeyError(f"Username '{username}' not found.")
        return self.user_table[username]


# Example usage
if __name__ == "__main__":
    user_hash_table = UserHashTable()

    # Adding users
    user_hash_table.add_user("john_doe", {"age": 30, "email": "john@example.com"})
    user_hash_table.add_user("jane_smith", {"age": 25, "email": "jane@example.com"})

    # Retrieving user profiles
    try:
        john_profile = user_hash_table.get_user("john_doe")
        print("John's Profile:", john_profile)

        jane_profile = user_hash_table.get_user("jane_smith")
        print("Jane's Profile:", jane_profile)

        # Attempting to retrieve a non-existent user
        user_hash_table.get_user("non_existent_user")  # This will raise a KeyError
    except KeyError as e:
        print(e)
    except ValueError as e:
        print(e)
