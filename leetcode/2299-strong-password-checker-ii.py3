class Solution:
    def strongPasswordCheckerII(self, password: str) -> bool:
        if len(password) < 8: return False
        if password == password.upper(): return False
        if password == password.lower(): return False
        if all(not ch.isdigit() for ch in password): return False
        if all(ch not in "!@#$%^&*()-+" for ch in password): return False
        return all(password[i] != password[i + 1] for i in range(len(password) - 1))
