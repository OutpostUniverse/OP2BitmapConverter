# For building on CircleCI with Google Test

# Build from the root project folder with:
#   docker build .circleci/ --tag outpostuniverse/op2bitmapconverter:1.0
# Push image to DockerHub with:
#   docker login
#   docker push outpostuniverse/op2bitmapconverter

# Run locally using the CircleCI command line interface:
#   circleci build
# Validate .circleci/config.yml file with:
#   circleci config validate

FROM outpostuniverse/op2utility:1.1

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    libgflags-dev \
  && rm -rf /var/lib/apt/lists/*
