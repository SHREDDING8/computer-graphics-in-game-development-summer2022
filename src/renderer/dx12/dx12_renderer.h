#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include "renderer/renderer.h"

#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include <Windows.h>
#include <d3dx12.h>
#include <dxgi1_4.h>
#include <exception>
#include <initguid.h>
#include <iostream>
#include <wrl.h>


using namespace Microsoft::WRL;

namespace cg::renderer
{
	class dx12_renderer : public renderer
	{
	public:
		virtual void init();
		virtual void destroy();

		virtual void update();
		virtual void render();

	protected:
		static const UINT frame_number = 2;

		// Pipeline objects.
		ComPtr<ID3D12Device> device;
		ComPtr<ID3D12CommandQueue> command_queue;
		ComPtr<IDXGISwapChain3> swap_chain;
		ComPtr<ID3D12DescriptorHeap> rtv_heap;
		ComPtr<ID3D12DescriptorHeap> cbv_heap;
		UINT rtv_descriptor_size;
		ComPtr<ID3D12Resource> render_targets[frame_number];
		ComPtr<ID3D12CommandAllocator> command_allocators[frame_number];
		ComPtr<ID3D12PipelineState> pipeline_state;
		ComPtr<ID3D12GraphicsCommandList> command_list;

		ComPtr<ID3D12RootSignature> root_signature;
		CD3DX12_VIEWPORT view_port;
		CD3DX12_RECT scissor_rect;

		// Resources
		std::vector<ComPtr<ID3D12Resource>> vertex_buffers;
		std::vector<D3D12_VERTEX_BUFFER_VIEW> vertex_buffer_views;

		std::vector<ComPtr<ID3D12Resource>> index_buffers;
		std::vector<D3D12_INDEX_BUFFER_VIEW> index_buffer_views;

		DirectX::XMMATRIX world_view_projection;
		ComPtr<ID3D12Resource> constant_buffer;
		UINT8* constant_buffer_data_begin;

		// Synchronization objects.
		UINT frame_index;
		HANDLE fence_event;
		ComPtr<ID3D12Fence> fence;
		UINT64 fence_values[frame_number];

		void load_pipeline();
		void load_assets();
		void populate_command_list();

		void move_to_next_frame();
		void wait_for_gpu();
	};
}// namespace cg::renderer