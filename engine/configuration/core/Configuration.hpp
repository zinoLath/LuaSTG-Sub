#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <optional>
#include <functional>

namespace core {
	struct Configuration {
	public:
		struct Include {
			std::string path;
			bool optional{ false };
		};

		std::vector<Include> include;

		struct Debug {
			std::optional<bool> track_window_focus;
		};

		std::optional<Debug> debug;

		struct Application {
			std::optional<std::string> uuid;
			std::optional<bool> single_instance;
		};

		std::optional<Application> application;

		enum class FileSystemType {
			normal,
			archive,
		};

		struct FileSystem {
			FileSystemType type{ FileSystemType::normal };
			std::string path;
		};

		struct Display {
			std::string device_name;
			int32_t left{};
			int32_t top{};
			int32_t right{};
			int32_t bottom{};
		};

		struct GraphicsSystem {
			std::optional<std::string> preferred_device_name;
			std::optional<uint32_t> width;
			std::optional<uint32_t> height;
			std::optional<bool> fullscreen;
			std::optional<bool> vsync;
			std::optional<Display> display;
		};

		struct AudioSystem {
			std::optional<std::string> preferred_endpoint_name;
			std::optional<float> sound_effect_volume;
			std::optional<float> music_volume;
		};

		struct InitApplication {
			std::optional<uint32_t> frame_rate;
		};

		struct InitWindow {
			std::optional<std::string> title;
			std::optional<bool> cursor_visible;
			std::optional<bool> allow_window_corner;
		};

		struct Initialize {
			std::vector<FileSystem> file_systems;

			std::optional<GraphicsSystem> graphics_system;

			std::optional<AudioSystem> audio_system;

			std::optional<InitApplication> application;

			std::optional<InitWindow> window;
		};

		std::optional<Initialize> initialize;

	private:
		std::function<void(std::string_view const&)> error_callback;

		bool allow_include{ false };

	public:
		void setErrorCallback(std::function<void(std::string_view const&)> const& cb);

		inline void setAllowInclude(bool const v) { allow_include = v; }

		bool loadFromFile(std::string_view const& path);

		Configuration();
	};

#define GetterSetterBoolean(_class_, _field_, _method_name_) \
	inline bool is##_method_name_ () const noexcept { return _field_ ; }; \
	inline _class_ & set##_method_name_ (bool const _field_##_ ) { _field_ = _field_##_ ; return *this; }

#define GetterSetterString(_class_, _field_, _method_name_) \
	inline bool has##_method_name_ () const noexcept { return !((_field_).empty()) ; }; \
	inline std::string const& get##_method_name_ () const noexcept { return _field_ ; }; \
	inline _class_ & set##_method_name_ (std::string const& _field_##_ ) { _field_ = _field_##_ ; return *this; }

#define GetterSetterPrimitive(_class_, _type_, _field_, _method_name_) \
	inline _type_ get##_method_name_ () const noexcept { return _field_ ; }; \
	inline _class_ & set##_method_name_ ( _type_ const _field_##_ ) { _field_ = _field_##_ ; return *this; }

	class ConfigurationLoader {
	public:
		class Debug {
		public:
			GetterSetterBoolean(Debug, track_window_focus, TrackWindowFocus);
		private:
			bool track_window_focus{ false };
		};
		class Application {
		public:
			GetterSetterString(Application, uuid, Uuid);
			GetterSetterBoolean(Application, single_instance, SingleInstance);
		private:
			std::string uuid;
			bool single_instance{ false };
		};
		class GraphicsSystem {
		public:
			GetterSetterString(GraphicsSystem, preferred_device_name, PreferredDeviceName);
			GetterSetterPrimitive(GraphicsSystem, uint32_t, width, Width);
			GetterSetterPrimitive(GraphicsSystem, uint32_t, height, Height);
			GetterSetterBoolean(GraphicsSystem, fullscreen, Fullscreen);
			GetterSetterBoolean(GraphicsSystem, vsync, Vsync);
		private:
			std::string preferred_device_name;
			uint32_t width{ 640 };
			uint32_t height{ 480 };
			bool fullscreen{};
			bool vsync{};
		};
		class AudioSystem {
		public:
			GetterSetterString(AudioSystem, preferred_endpoint_name, PreferredEndpointName);
			GetterSetterPrimitive(AudioSystem, float, sound_effect_volume, SoundEffectVolume);
			GetterSetterPrimitive(AudioSystem, float, music_volume, MusicVolume);
		private:
			std::string preferred_endpoint_name;
			float sound_effect_volume{ 1.0 };
			float music_volume{ 1.0f };
		};
		class InitApplication {
		public:
			GetterSetterPrimitive(InitApplication, uint32_t, frame_rate, FrameRate);
		private:
			uint32_t frame_rate{ 60 };
		};
		class InitWindow {
		public:
			GetterSetterString(InitWindow, title, Title);
			GetterSetterBoolean(InitWindow, cursor_visible, CursorVisible);
			GetterSetterBoolean(InitWindow, allow_window_corner, AllowWindowCorner);
		private:
			std::string title;
			bool cursor_visible{ true };
			bool allow_window_corner{ true };
		};
		class Initialize {
			friend class ConfigurationLoader;
		public:
			inline std::vector<Configuration::FileSystem> const& getFileSystems() const noexcept { return file_systems; }
			inline GraphicsSystem const& getGraphicsSystem() const noexcept { return graphics_system; }
			inline AudioSystem const& getAudioSystem() const noexcept { return audio_system; }
			inline InitApplication const& getApplication() const noexcept { return application; }
			inline InitWindow const& getWindow() const noexcept { return window; }
		private:
			std::vector<Configuration::FileSystem> file_systems;
			GraphicsSystem graphics_system;
			AudioSystem audio_system;
			InitApplication application;
			InitWindow window;
		};
	public:
		void merge(Configuration const& config);
		bool loadFromFile(std::string_view const& path);
		inline std::vector<std::string> const& getMessages() const noexcept { return messages; }
		std::string getFormattedMessage();
		inline Debug const& getDebug() const noexcept { return debug; }
		inline Application const& getApplication() const noexcept { return application; }
		inline Initialize const& getInitialize() const noexcept { return initialize; }
	public:
		static bool exists(std::string_view const& path);
		static ConfigurationLoader& getInstance();
	private:
		void mergeOnly(Configuration const& config);
		void applyOnly();
	private:
		std::vector<std::string> messages;
		Configuration configuration;
		Debug debug;
		Initialize initialize;
		Application application;
	};

#undef GetterSetterBoolean
#undef GetterSetterString
#undef GetterSetterPrimitive
}
