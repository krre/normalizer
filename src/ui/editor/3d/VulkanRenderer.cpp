#include "VulkanRenderer.h"
#include <QVulkanFunctions>

VulkanRenderer::VulkanRenderer(QVulkanWindow* window) : m_window(window) {

}

void VulkanRenderer::initResources() {
    VkDevice dev = m_window->device();
    m_devFuncs = m_window->vulkanInstance()->deviceFunctions(dev);
}

void VulkanRenderer::releaseResources() {

}

void VulkanRenderer::startNextFrame() {
    VkCommandBuffer cb = m_window->currentCommandBuffer();
    QSize size = m_window->swapChainImageSize();

    VkClearColorValue clearColor = {{ 0.7, 0.5, 0.7, 1 }};
    VkClearDepthStencilValue clearDepthStencil = { 1, 0 };
    VkClearValue clearValues[3];
    memset(clearValues, 0, sizeof(clearValues));
    clearValues[0].color = clearValues[2].color = clearColor;
    clearValues[1].depthStencil = clearDepthStencil;

    VkRenderPassBeginInfo rpBeginInfo;
    memset(&rpBeginInfo, 0, sizeof(rpBeginInfo));
    rpBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rpBeginInfo.renderPass = m_window->defaultRenderPass();
    rpBeginInfo.framebuffer = m_window->currentFramebuffer();
    rpBeginInfo.renderArea.extent.width = size.width();
    rpBeginInfo.renderArea.extent.height = size.height();
    rpBeginInfo.clearValueCount = m_window->sampleCountFlagBits() > VK_SAMPLE_COUNT_1_BIT ? 3 : 2;
    rpBeginInfo.pClearValues = clearValues;

    VkCommandBuffer cmdBuf = m_window->currentCommandBuffer();
    m_devFuncs->vkCmdBeginRenderPass(cmdBuf, &rpBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

    VkViewport viewport;
    viewport.x = viewport.y = 0;
    viewport.width = size.width();
    viewport.height = size.height();
    viewport.minDepth = 0;
    viewport.maxDepth = 1;
    m_devFuncs->vkCmdSetViewport(cb, 0, 1, &viewport);

    VkRect2D scissor;
    scissor.offset.x = scissor.offset.y = 0;
    scissor.extent.width = viewport.width;
    scissor.extent.height = viewport.height;
    m_devFuncs->vkCmdSetScissor(cb, 0, 1, &scissor);

    m_devFuncs->vkCmdEndRenderPass(cmdBuf);

    m_window->frameReady();
}
