import tornado.ioloop
import tornado.web
import os


def make_app():
    static_settings = {
        'path': os.path.join(os.path.dirname(__file__), '../resource'),
    }
    return tornado.web.Application([
        (r"/(\S+\.html)", tornado.web.StaticFileHandler, static_settings),
    ])


if __name__ == "__main__":
    app = make_app()
    app.listen(8081)
    tornado.ioloop.IOLoop.current().start()
