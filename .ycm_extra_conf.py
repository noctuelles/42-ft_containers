def Settings( **kwargs ):
  return {
    'flags': [ '-x', 'c++', '-Wall', '-Werror', '-Wextra', '-std=c++11', '-I', 'includes'],
  }
