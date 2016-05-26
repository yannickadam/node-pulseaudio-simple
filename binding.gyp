{
  "targets": [
    {
      "target_name": "npas",
      "sources": [ "src/pa-simple-binding.cc" ],
      'link_settings': {
          'libraries': [
            '-lpulse',
            '-lpulse-simple'
          ]
      }
    }
  ]
}
