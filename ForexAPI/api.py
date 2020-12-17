import flask
from flask import request, jsonify

app = flask.Flask(__name__)
app.config["DEBUG"] = True

prediction = {"prediction":
                  {'id': 0,
                   'title': 'A Fire Upon the Deep',
                   'author': 'Vernor Vinge',
                   'first_sentence': 'The coldsleep itself was dreamless.',
                   'year_published': '1992'
                   }
              }

# A route to return all of the available entries in our catalog.
@app.route('/api/forex/prediction', methods=['GET'])
def api_all():
    return jsonify(prediction)


@app.route('/', methods=['GET'])
def home():
    return "<h1>Distant Reading Archive</h1><p>This site is a prototype API for distant reading of science fiction novels.</p>"


app.run()
