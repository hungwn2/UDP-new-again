/************************************************************************************************
 * @file   client.cc
 *
 * @brief  Source file defining the Client class for UDP communication
 *
 * @date   2025-01-04
 * @author Aryan Kashem
 ************************************************************************************************/

/* Standard library Headers */
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <unistd.h>

/* Inter-component Headers */

/* Intra-component Headers */
#include "client.h"

void Client::processMessagesProcedure() {
  while (m_isConnected) {
    sem_wait(&m_messageSemaphore);

    pthread_mutex_lock(&m_mutex);

    if (!m_messageQueue.empty()) {
      auto message = m_messageQueue.front();
      m_messageQueue.pop();

      if (m_messageCallback) {
        m_messageCallback(this, message);
      }
    }

    pthread_mutex_unlock(&m_mutex);
  }
}

void Client::receiverProcedure() {
  while (m_isConnected) {
    std::string buffer(MAX_BUFFER_SIZE, '\0');
    socklen_t addrLen = sizeof(m_serverAddress);

    ssize_t bytesRead = recvfrom(m_socketFd, &buffer[0], MAX_BUFFER_SIZE, 0,
                                 (struct sockaddr *)&m_serverAddress, &addrLen);
    if (bytesRead < 0) {
      std::cerr << "Error receiving message" << std::endl;
      continue;
    }

    buffer.resize(bytesRead);

    pthread_mutex_lock(&m_mutex);
    m_messageQueue.push(buffer);
    pthread_mutex_unlock(&m_mutex);

    sem_post(&m_messageSemaphore);
  }
}

void *receiverProcedureWrapper(void *param) {
  Client *client = static_cast<Client *>(param);
  try {
    client->receiverProcedure();
  } catch (std::exception &e) {
    std::cerr << "Receiver Thread Error: " << e.what() << std::endl;
  }
  return nullptr;
}

void *processMessagesProcedureWrapper(void *param) {
  Client *client = static_cast<Client *>(param);
  try {
    client->processMessagesProcedure();
  } catch (...) {
    std::cerr << "Process Messages Thread Error" << std::endl;
  }
  return nullptr;
}

void Client::start() {
  try {
    m_socketFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_socketFd < 0)
      throw std::runtime_error("Failed to create socket");

    m_serverAddress.sin_family = AF_INET;
    m_serverAddress.sin_port = htons(m_port);

    if (inet_pton(AF_INET, m_host.c_str(), &m_serverAddress.sin_addr) <= 0)
      throw std::runtime_error("Invalid server address");

    m_isConnected = true;

    if (pthread_create(&m_receiverThreadId, NULL, receiverProcedureWrapper, this) != 0)
      throw std::runtime_error("Failed to create receiver thread");

    if (pthread_create(&m_processMessageThreadId, NULL, processMessagesProcedureWrapper, this) != 0)
      throw std::runtime_error("Failed to create process messages thread");

  } catch (const std::exception &e) {
    std::cerr << "Error starting client: " << e.what() << std::endl;
    m_isConnected = false;
  }
}

void Client::disconnectServer() {
  m_isConnected = false;
  if (m_socketFd >= 0) {
    close(m_socketFd);
    m_socketFd = -1;
  }
}

void Client::sendMessage(const std::string &message) {
  socklen_t addrLen = sizeof(m_serverAddress);
  ssize_t sent = sendto(m_socketFd, message.c_str(), message.size(), 0,
                        (struct sockaddr *)&m_serverAddress, addrLen);
  if (sent < 0) {
    throw std::runtime_error("Failed to send message");
  }
}

bool Client::isConnected() const {
  return m_isConnected;
}

Client::Client(const std::string &host, int port, messageCallback msgCb)
    : m_host(host), m_port(port), m_messageCallback(msgCb), m_isConnected(false), m_socketFd(-1) {
  if (pthread_mutex_init(&m_mutex, nullptr) != 0) {
    throw std::runtime_error("Failed to initialize mutex");
  }

  if (sem_init(&m_messageSemaphore, 0, 0) != 0) {
    throw std::runtime_error("Failed to initialize semaphore");
  }
}

Client::~Client() {
  disconnectServer();
  pthread_mutex_destroy(&m_mutex);
  sem_destroy(&m_messageSemaphore);
}
