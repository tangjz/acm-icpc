class FileSystem:

    def __init__(self):
        self.paths = {}

    def createPath(self, path: str, value: int) -> bool:
        if not path.startswith('/') or path.endswith('/'): return False
        items = path[1:].split('/')
        prefix = ""
        for item in items:
            prefix += '/' + item
            if prefix.endswith('/'): return False
            if len(prefix) < len(path) and prefix not in self.paths: return False
        if path in self.paths: return False
        self.paths[path] = value
        return True

    def get(self, path: str) -> int:
        return self.paths.get(path, -1)


# Your FileSystem object will be instantiated and called as such:
# obj = FileSystem()
# param_1 = obj.createPath(path,value)
# param_2 = obj.get(path)
