(function() {

  if (typeof Module == 'undefined') Module = {};

  if (typeof Module['setStatus'] == 'undefined') {
    Module['setStatus'] = function (status) {
      document.getElementById('status').textContent = status;
    };
  }

  if (typeof Module['canvas'] == 'undefined') {
    Module['canvas'] = document.getElementById('canvas');
  }

  function getLoggerTime() {
    var date = new Date();
    return date.getHours() + ":" + date.getMinutes() + ":" + date.getSeconds() + ":" + date.getMilliseconds();
  }

  function log(msg) {
    var parent = document.getElementById('log');
    if (parent.childNodes.length > 200) {
      parent.removeChild(parent.childNodes[0]);
    }

    var logElem = document.createElement('div');
    logElem.textContent = getLoggerTime() + ": " + msg;
    parent.appendChild(logElem);
  }

  if (!Module['_main']) Module['_main'] = function() {
    var im_open_decoder = Module.cwrap('im_open_decoder', 'number', ['string', 'string']);
    var im_reset_search = Module.cwrap('im_reset_search', '', []);
    var im_search = Module.cwrap('im_search', 'number', ['string', 'number']);
    var im_get_candidate = Module.cwrap('im_get_candidate', 'string', ['number', 'string', 'number']);
    var im_get_candidate_char = Module.cwrap('im_get_candidate_char', 'string', ['number']);

    log('Data file is ready');
    log('Opening data/dict.data ....');
    if (im_open_decoder('data/dict.data', 'user.dict')) {
      log('Success to open data/dict.data!');
    } else {
      log('Failed to open data/dict.data!');
    }

    document.getElementById('test_nia').onclick = function() {
      test('nia');
    };

    document.getElementById('test_aig').onclick = function() {
      test('aig');
    };

    document.getElementById('test_qua').onclick = function() {
      test('qua');
    };

    function test(keyword) {
      try {
        im_reset_search();

        log('search keyword ' + keyword);
        var startTime = new Date().getTime();
        var size = im_search(keyword, keyword.length);
        var endTime = new Date().getTime();

        log('got ' + size + ' candidates, cost ' + (endTime - startTime) + ' milliseconds.');

        var candidates = '';
        for (var i = 0; i < size; i++) {
          candidates += im_get_candidate_char(i) + ' ';
        }
        log('Candidates: ' + candidates);
      } catch (e) {
        log('error: ' + e);
      }
    };
  }

})();

